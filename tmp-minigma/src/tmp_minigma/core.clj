(ns tmp-minigma.core
  (:require [clojure.test :refer :all]
            [clojure.string :as s]))

(def rotor-position-1 (atom 4))
(def rotor-position-2 (atom 0))
(def rotor-position-3 (atom 0))

(def alfabeth        "abcdefghijklmnopqrstuvwxyz")
(def rotor-1         "ekmflgdqvzntowyhxuspaibrcj")
(def rotor-1-reverse "uwygadfpvzbeckmthxslrinqoj")
(def rotor-2         "ajdksiruxblhwtmcqgznpyfvoe")
(def rotor-2-reverse "ajpczwrlfbdkotyuqgenhxmivs")
(def rotor-3         "bdfhjlcprtxvznyeiwgakmusqo")
(def rotor-3-reverse "tagbpcsdqeufvnzhyixjwlrkom")
(def reflector       "ejmzalyxvbwfcrquontspikhgd")

(defn ord [c]
  (- (int c) (int \a)))

(defn dro [n]
  (char (+ n (int \a))))

(defn reverse-rotor [rotor]
  (apply str (map #(dro (.indexOf rotor (int %))) alfabeth)))

(defn alfa [c]
  (and (char? c) (<= (ord \a) (ord c) (ord \z))))

(defn set-start-rotor [first second third]
  (reset! rotor-position-1 first)
  (reset! rotor-position-2 second)
  (reset! rotor-position-3 third))

(defn rotate [c rotation]
  {:pre [(alfa c)]
   :post [(alfa c)]}
  #dbg (let [i (ord c)
        r (mod rotation 26)
        n (+ (int \a) (mod (+ i r) 26))]
    (char n)))

(defn translate [c translation]
  {:pre [(alfa c)]
   :post ([alfa %])}
  #dbg (.charAt translation (ord c)))

(defn rotors [n]
  (let [r1 (mod n (Math/pow 26 3))]))

(defn enigmate [c]
  (swap! rotor-position-1 inc)
  (when (>= @rotor-position-1 26)
    (reset! rotor-position-1 0)
    (swap! rotor-position-2 inc))
  (when (>= @rotor-position-2 26)
    (reset! rotor-position-2 0)
    (swap! rotor-position-3 inc))
  (when (>= @rotor-position-3 26)
    (reset! rotor-position-3 0))
  (prn @rotor-position-3 "  |  " @rotor-position-2 "  |  " @rotor-position-1 )

  (-> c
      (rotate @rotor-position-1)
      (translate rotor-1)

      (rotate @rotor-position-2)
      (translate rotor-2)

      (rotate @rotor-position-3)
      (translate rotor-3)

      (translate reflector)

      (translate rotor-3-reverse)
      (rotate (- @rotor-position-3))

      (translate rotor-2-reverse)
      (rotate (- @rotor-position-2))

      (translate rotor-1-reverse)
      (rotate (- @rotor-position-1))))

(defn enigmate-string [s]
  (apply str (map enigmate s)))

(deftest rotate-test
  (testing "rotate by 0 is the same"
    (is (= \a (rotate \a 0))))
  (testing "rotate by 1 is the next letter"
    (is (= \b (rotate \a 1))))
  (testing "rotate by 26  is the same letter again"
    (is (= \a (rotate \a 26))))
  (testing "rotate by 26+1  is the next letter again"
    (is (= \b (rotate \a 27)))))

(deftest translate-test
  (testing "translate a->b when b is the first letter in the translation string"
    (is (= \b (translate \a "bacdefghijklmnopqrstuvwxyz"))))
  (testing "translate z->d when d is the last letter in the translation string"
    (is (= \d (translate \z "bacdefghijklmnopqrstuvwxyd")))))

(deftest rotors-test
  (testing "1 is [1 1 1]")
  (testing "2 is [1 1 2]")
  (testing "26 is [1 1 26]"))

(deftest enigmate-test
  (testing "encrption should be symetric"
    (is (= \a (enigmate (enigmate \a)))))
  (testing "encrption should be symetric"
    (is (= \b (enigmate (enigmate \b)))))
  (testing "encrption should be symetric"
    (is (= \z (enigmate (enigmate \z))))))


(deftest symetric-test
  (let [_ (set-start-rotor 4 6 3)
        encoded (enigmate-string "testabc")
        _ (set-start-rotor 4 6 3)
        decoded (enigmate-string encoded)]
    (is (= "testabc" decoded))))
