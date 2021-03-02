import os
import random
import sys
import time
from argparse import ArgumentParser
from collections import deque
from pprint import pformat
from typing import Union

os.environ["PYGAME_HIDE_SUPPORT_PROMPT"] = "1"

import pygame.display
import pygame.event
import pygame.font
from pygame import Color, Rect, Surface, draw

SNAKE_COLOR = Color("green")
APPLE_COLOR = Color("red")
QUIT = object()


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __getitem__(self, ix):
        if ix == 0 or ix == "x":
            return self.x

        if ix == 1 or ix == "y":
            return self.y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __add__(self, other):
        return Point(self.x + other[0], self.y + other[1])

    def __radd__(self, other):
        return Point(self.x + other[0], self.y + other[1])

    def __sub__(self, other):
        return Point(self.x - other[0], self.y - other[1])

    def __rsub__(self, other):
        return Point(other[0] - self.x, other[1] - self.y)

    def __repr__(self):
        return f"Point({self.x}, {self.y})"

    def __hash__(self):
        return hash((self.x, self.y))


class State:
    def __init__(self, world_size):
        self.world_size = world_size
        initial_position = Point(world_size[0] // 2, world_size[1] // 2)
        self.direction: Point = Point(1, 0)
        self.snake_bits = deque(
            (
                initial_position - (2, 0),
                initial_position - (1, 0),
                initial_position,
            )
        )
        self.apples: list[Point] = [
            Point(random.randint(0, world_size[0]), random.randint(0, world_size[1]))
        ]
        self.future_snake_bit: Union[Point, None] = None

    def __repr__(self):
        return pformat(
            {
                "world_size": self.world_size,
                "direction": self.direction,
                "snake_bits": self.snake_bits,
                "apples": self.apples,
            }
        )

    def new_apple(self):
        valid_points = set(
            Point(x, y)
            for x in range(self.world_size[0])
            for y in range(self.world_size[1])
        ) - set(self.snake_bits)
        self.apples.append(random.sample(valid_points, 1)[0])


class Grid:
    def __init__(self, size):
        self.size = size

    def _dim_to_span(self, ix, dim) -> Point:
        width = dim / self.size
        return Point(ix * width, ix * width + width - 1)

    def to_rect(self, grid_point: Point, surface_dim: tuple[int, int]) -> Rect:
        width = surface_dim[0] // self.size[0]
        height = surface_dim[1] // self.size[1]
        return Rect((grid_point.x * width, grid_point.y * height), (width, height))


def process_input():
    events = pygame.event.get()
    for event in events:
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_s:
                return Point(0, 1)
            if event.key == pygame.K_w:
                return Point(0, -1)
            if event.key == pygame.K_a:
                return Point(-1, 0)
            if event.key == pygame.K_d:
                return Point(1, 0)
            if event.key == pygame.K_ESCAPE:
                return QUIT

    return None


def _collided_with_boundary(head, world_size):
    return (
        head.x < 0 or head.x == world_size[0] or head.y < 0 or head.y == world_size[1]
    )


def update_state(state: State, new_direction: Union[Point, None]) -> bool:
    if (
        new_direction is not None
        and new_direction[0] != -state.direction[0]
        and new_direction[1] != -state.direction[1]
    ):
        state.direction = new_direction

    snake_bits = state.snake_bits
    if state.future_snake_bit is None or snake_bits[0] != state.future_snake_bit:
        snake_bits.popleft()
    else:
        state.future_snake_bit = None

    tail = [snake_bits[ix] for ix in range(len(snake_bits) - 1)]
    if snake_bits[-1] in tail or _collided_with_boundary(
        snake_bits[-1], state.world_size
    ):
        return False

    if snake_bits[-1] in state.apples:
        apple_ix = state.apples.index(snake_bits[-1])
        the_apple = state.apples[apple_ix]
        state.future_snake_bit = the_apple
        state.apples.pop(apple_ix)
        state.new_apple()

    snake_bits.append(snake_bits[-1] + state.direction)

    return True


def redraw(surface: Surface, grid: Grid, state: State):
    surface_size = surface.get_size()
    surface.fill(Color("black"))

    for apple in state.apples:
        draw.rect(surface, SNAKE_COLOR, grid.to_rect(apple, surface_size))

    for snake_bit in state.snake_bits:
        draw.rect(surface, APPLE_COLOR, grid.to_rect(snake_bit, surface_size))


def death_screen(surface: Surface, state: Union[State, None]):
    mid_y = surface.get_height() // 2
    surface.fill(Color("black"))
    font = pygame.font.Font(None, 36)
    font_small = pygame.font.Font(None, 28)

    cont = True
    while cont:
        time.sleep(0.001)
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.KEYUP:
                if event.key != pygame.K_ESCAPE:
                    return True
                return False

        if state is None:
            msg = "esc: quit, any other key: new game"
            text = font.render(msg, False, Color("gray"))
            textpos = text.get_rect(centerx=surface.get_width() / 2, top=mid_y)
            surface.blit(text, textpos)
            pygame.display.flip()
        else:
            msg = [
                "GAME OVER",
                f"SCORE: {len(state.snake_bits)}",
                "esc: quit, any other key: new game",
            ]
            text = font.render(msg[0], True, APPLE_COLOR)
            textpos = text.get_rect(
                centerx=surface.get_width() / 2, top=mid_y - font.get_linesize() / 2
            )
            surface.blit(text, textpos)

            text = font.render(msg[1], True, SNAKE_COLOR)
            textpos = text.get_rect(
                centerx=surface.get_width() / 2, top=mid_y + font.get_linesize() / 2
            )
            surface.blit(text, textpos)

            text = font_small.render(msg[2], True, Color("gray"))
            textpos = text.get_rect(
                centerx=surface.get_width() / 2, top=mid_y + 3 * font.get_linesize() / 2
            )
            surface.blit(text, textpos)
            pygame.display.flip()


def game_loop(args):
    grid = Grid(args.world_size)
    state = State(args.world_size)

    last_update = time.monotonic()
    cont = True
    new_direction = deque(maxlen=2)
    while cont:
        loop_start = time.monotonic()
        maybe_new_direction = process_input()
        if maybe_new_direction is QUIT:
            break
        elif maybe_new_direction is not None:
            new_direction.append(maybe_new_direction)

        if loop_start - last_update > 0.125:
            cont = update_state(
                state, new_direction.popleft() if new_direction else None
            )
            last_update = loop_start

        redraw(pygame.display.get_surface(), grid, state)
        pygame.display.flip()
        time.sleep(0.001)

    return state


def game(args):
    pygame.font.init()
    screen = pygame.display.set_mode((600, 600), pygame.HWSURFACE | pygame.DOUBLEBUF)

    state = None
    while True:
        play = death_screen(pygame.display.get_surface(), state)
        if play:
            state = game_loop(args)
        else:
            break


def parse_args(sys_args):
    parser = ArgumentParser()
    parser.add_argument("--world-size", type=int, nargs=2, default=(50, 50))
    return parser.parse_known_args(sys_args)


def main():
    args = parse_args(sys.argv)
    game(args[0])
