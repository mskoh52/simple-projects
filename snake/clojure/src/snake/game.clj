(ns snake.game
  (:require
   [snake.game-state :refer [init-state]]
   [snake.state-machine :refer [transition]])
  (:use [seesaw.core] [seesaw.graphics]))

(defn -push-max-2 [q x] (if (= (count q) 2) (-> q pop (conj x)) (conj q x)))

(defn -key-handler [game-state]
  (fn [event]
    (dosync
     (let [key (-> event .getKeyCode java.awt.event.KeyEvent/getKeyText)]
       (let [new-state (cond (= "W" key) (alter game-state update :direction-queue -push-max-2 [0 -1])
                             (= "A" key) (alter game-state update :direction-queue -push-max-2 [-1 0])
                             (= "S" key) (alter game-state update :direction-queue -push-max-2 [0 1])
                             (= "D" key) (alter game-state update :direction-queue -push-max-2 [1 0])
                             (= "Escape" key) (alter game-state assoc :dead true))]
         new-state)))))

(defn -render [state]
  (fn [c g]
    (let [{:keys [:world-size :snake-bits :apple]} @state
          canvas-width (.getWidth c)
          canvas-height (.getHeight c)
          grid-px-width (Math/floor (/ canvas-width (first world-size)))
          grid-px-height (Math/floor (/ canvas-height (last world-size)))
          -draw-rect (fn [g x y color]
                       (draw g (rect (* x grid-px-width) (* y grid-px-height)
                                     grid-px-width grid-px-height)
                             (style :background color)))]
      (-draw-rect g (first apple) (last apple) :green)
      (doseq [[x y] snake-bits] (-draw-rect g x y :red)))))

(defn transition-to-game [app-state]
  (println "transitioning to game")
  (let [frame (:frame app-state)
        game-state (init-state [50 50])
        cvs (select frame [:#canvas])]
    (config! cvs :paint (-render game-state))
    (assoc app-state
           :game-state game-state
           :listeners (list (listen frame :key-pressed (-key-handler game-state))))))

(comment
  (def q (clojure.lang.PersistentQueue/EMPTY))
  (seq (-push-max-2 q [0 -1])))
