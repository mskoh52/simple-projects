(ns snake.core
  (:require [snake.game :refer [transition-to-game]]
            [snake.menu :refer [transition-to-menu]]
            [snake.game-state :refer [init-state compute-state]]
            [snake.state-machine :refer [transition]])
  (:use [seesaw.core]))

(defn transition-to-quit [app-state]
  (println "transitioning to quit")
  (dispose! (:frame app-state))
  (System/exit 0)
  app-state)

(defn -main-loop [app-state]
  (dosync
   (let [current-state (:current-state app-state)
         next-state (deref (:next-state app-state))
         tick (:tick app-state)]
     (if (and (not (nil? (:game-state app-state))) (= 0 tick))
       (alter (:game-state app-state) compute-state))
     (repaint! (select (:frame app-state) [:#canvas]))
     (if (and (not (nil? (:game-state app-state))) (:dead @(:game-state app-state))) ; TODO move this to game.clj
       (ref-set (:next-state app-state) :menu))
     (update (if (= current-state next-state)
               app-state
               (transition app-state next-state))
             :tick
             #(mod (inc %) 100)))))

(defn -main [& args]
  (let [the-frame (frame :title "SNAKE"
                         :on-close :exit
                         :width 600
                         :height 600
                         :content (border-panel
                                   :id :border-panel
                                   :hgap 0
                                   :vgap 0
                                   :border 0
                                   :center (canvas :id :canvas
                                                   :background "#000"
                                                   :paint nil
                                                   :size [600 :by 600])))
        app-state {:current-state :init
                   :next-state (ref :menu)
                   :tick 0
                   :frame the-frame
                   :listeners nil
                   :game-state nil
                   :state-machine {:init {:menu transition-to-menu}
                                   :menu {:game transition-to-game :quit transition-to-quit}
                                   :game {:menu transition-to-menu}}}
        t (timer -main-loop :initial-value app-state :delay 1 :start? false)]
    (listen the-frame :window-opened (fn [_] (println "starting") (.start t)))
    (listen the-frame :window-closing (fn [_] (println "closing") (.stop t)))
    (invoke-later (-> the-frame pack! show!))))

(comment
  (use 'seesaw.core)
  (use 'seesaw.dev)
  (use 'seesaw.graphics)
  (use 'seesaw.font)
  (println (font-families))

  (show-options (frame))
  (show-events (frame))
  (.getHeight (select f [:#canvas]))

  (def f (frame :title "SNAKE"
                :on-close :exit
                :width 600
                :height 600
                :content (border-panel
                          :id :border-panel
                          :hgap 0
                          :vgap 0
                          :border 0
                          :center (canvas :id :canvas
                                          :background "#000"
                                          :paint nil
                                          :size [600 :by 600]))))
  (def -state (init-state [50 50]))

  (def snake-bits (:snake-bits @-state))

  snake-bits

  (compute-state @-state)
  (-main))
