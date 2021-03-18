(ns snake.pair)

(defn add [[x1 y1] [x2 y2]] [(+ x1 x2) (+ y1 y2)])
(defn sub [[x1 y1] [x2 y2]] [(- x1 x2) (- y1 y2)])
(defn times [[x1 y1] [x2 y2]] [(* x1 x2) (* y1 y2)])
(defn random-pair [[x-max y-max]] [(rand-int x-max) (rand-int y-max)])
