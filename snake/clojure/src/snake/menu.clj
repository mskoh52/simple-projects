(ns snake.menu
  (:require [snake.state-machine :refer [transition]])
  (:use [seesaw.core] [seesaw.graphics]))

(defn -key-handler [app-state]
  (fn [event]
    (dosync
     (let [key (-> event .getKeyCode java.awt.event.KeyEvent/getKeyText)
           next-state (:next-state app-state)]
       (cond (= "Escape" key) (ref-set next-state :quit)
             (= "Enter" key) nil
             :else (ref-set next-state :game))))))

(defn -render [state]
  (fn [c g]
    (let [canvas-width (.getWidth c)
          canvas-height (.getHeight c)
          midX (quot canvas-width 2)
          midY (quot canvas-height 2)]
      (if (not (nil? state))
        (do (draw g (string-shape (- midX 100) midY "GAME OVER")
                  (style :foreground :red :font "Sans-48"))
            (draw g (string-shape (- midX 100) (+ midY 50) (str "SCORE: " (count (:snake-bits @state))))
                  (style :foreground :green :font "Sans-48")))))))

(defn transition-to-menu [app-state]
  (println "transitioning to menu")
  (let [frame (:frame app-state)
        cvs (select frame [:#canvas])]
    (config! cvs :paint (-render (:game-state app-state)))
    (-> app-state
        (assoc :game-state nil)
        (assoc :listeners (list (listen frame :key-pressed (-key-handler app-state)))))))
