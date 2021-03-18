(ns snake.state-machine)

(defn transition [app-state transition-to]
  (doseq [listener (:listeners app-state)] (listener))
  (-> (dissoc app-state :listeners)
      ((get-in app-state [:state-machine (:current-state app-state) transition-to]))
      (assoc :current-state transition-to)))

(comment
  (def state-machine {:menu {:game configure-for-game :quit configure-quit}
                      :game {:menu configure-for-menu}})
  (def app-state {:current-state :menu
                  :frame nil
                  :listeners '()
                  :timers '()
                  :game-state nil})
  (def transition (make-transition-fn state-machine app-state)))
