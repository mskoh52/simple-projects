(ns snake.game-state
  (:require [snake.pair :refer [add random-pair sub times]]))

(defn init-state [world-size]
  (let [initial-position (map #(/ % 2) world-size)]
    (ref {:apple (random-pair world-size)
          :dead false
          :direction [1 0]
          :direction-queue (clojure.lang.PersistentQueue/EMPTY)
          :future-snake-bit nil
          :snake-bits [(sub initial-position [2 0])
                       (sub initial-position [1 0])
                       initial-position]
          :world-size world-size})))

(defn -next-direction [current-direction next-direction]
  (if (or (nil? next-direction)
          (= current-direction (times [-1 -1] next-direction)))
    current-direction
    next-direction))

(defn -next-head [snake-bits direction]
  (add (last snake-bits) direction))

(defn -eat-apple [state]
  (let [{:keys [apple snake-bits world-size]} state
        head (first snake-bits)]
    (if (= head apple)
      (assoc state :future-snake-bit apple :apple (random-pair world-size))
      state)))

(defn -is-dead? [next-head snake-bits world-size]
  (let [x (first next-head) y (last next-head)]
    (or (= x -1) (= y -1)
        (= x (first world-size)) (= y (last world-size))
        (contains? (set snake-bits) next-head))))

(defn compute-state [old-state]
  (let [{:keys [apple
                direction
                direction-queue
                future-snake-bit
                snake-bits
                world-size]} old-state
        next-direction (-next-direction direction (peek direction-queue))
        next-head (-next-head snake-bits next-direction)
        dead (-is-dead? next-head snake-bits world-size)
        eating (= next-head apple)]
    (assoc old-state
           :apple (if eating (random-pair world-size) apple)
           :dead dead
           :direction next-direction
           :direction-queue (pop direction-queue)
           :future-snake-bit (cond eating apple
                                   (= (first snake-bits) future-snake-bit) nil
                                   :else future-snake-bit)
           :snake-bits (if dead
                         snake-bits
                         (conj (subvec snake-bits (if (= (first snake-bits) future-snake-bit) 0 1))
                               next-head)))))

(comment
  (def -state @(init-state [50 50]))
  -state
  (-eat-apple -state)
  (-update-position (:snake-bits -state) (:direction -state) [0 -1] nil)
  (-> -state (update :direction-queue conj [0 -1]) compute-state))
