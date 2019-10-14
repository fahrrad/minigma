(ns tmp-minigma.core
  (:require [clojure.test :refer :all]))

(defn ord [c]
  (- (int c) (int \a)))

(defn rotate [c rotation]
  (let [i (ord c)
        r (mod rotation 26)
        n (+ (int \a) (mod (+ i r) 26))]
    (char n)))

(defn translate [i translation]
  (.charAt translation (ord i)))

(defn rotors [n]
  (let [r1 (mod n (pow 26 3))]))

(defn enigmate [])

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
