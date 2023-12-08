package main

import (
	"fmt"
	"testing"
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

func TestStackSPUSH(t *testing.T) {
	var stack Stack

	testCases := []struct {
		value   string
		isError bool
	}{
		{"value1", false},
		{"value2", false},
		{"value3", false},
	}

	for _, tc := range testCases {
		t.Run(tc.value, func(t *testing.T) {
			err := stack.SPUSH(tc.value)
			if err != nil && !tc.isError {
				t.Errorf("Expected SPUSH to fail, but got error: %v", err)
			} else if err == nil && tc.isError {
				t.Error("Expected SPUSH to succeed, but got no error")
			}
		})
	}
}

func TestStackSPOP(t *testing.T) {
	var stack Stack

	// Наполняем стек значениями
	stack.SPUSH("value1")
	stack.SPUSH("value2")
	stack.SPUSH("value3")

	// Извлекаем все значения
	for i := 2; i >= 0; i-- {
		t.Run(fmt.Sprintf("Pop%d", i), func(t *testing.T) {
			value, err := stack.SPOP()
			if err != nil {
				t.Errorf("Expected SPOP to succeed, but got error: %v", err)
			}

			expectedValue := fmt.Sprintf("value%d", i+1)
			if value != expectedValue {
				t.Errorf("Expected SPOP value to be %s, but got %s", expectedValue, value)
			}
		})
	}
}
