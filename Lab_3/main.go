package main

import (
	"fmt"
)

const SIZE = 901

type Stack struct {
	elements [SIZE]string
	top      int
}

func (s *Stack) SPUSH(value string) error {
	if s.top < SIZE-1 {
		s.top++
		s.elements[s.top] = value
		return nil
	}
	return fmt.Errorf("Stack is full")
}

func (s *Stack) SPOP() (string, error) {
	if s.top == -1 {
		return "", fmt.Errorf("Stack is empty")
	}

	value := s.elements[s.top]
	s.elements[s.top] = ""
	s.top--
	return value, nil
}
