package main

import (
	"fmt"
	"testing"
)

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

func TestStackSPOPWithEmptyStack(t *testing.T) {
	var stack Stack

	t.Run("PopFromEmptyStack", func(t *testing.T) {
		_, err := stack.SPOP()
		if err != nil {
			t.Error("Expected SPOP to fail with empty stack, but got no error")
		}
	})
}

func TestStackSPUSHFullStack(t *testing.T) {
	var stack Stack

	// Заполняем стек
	for i := 0; i < SIZE; i++ {
		stack.SPUSH(fmt.Sprintf("value%d", i+1))
	}

	t.Run("PushToFullStack", func(t *testing.T) {
		err := stack.SPUSH("extraValue")
		if err == nil {
			t.Error("Expected SPUSH to fail with full stack, but got no error")
		}
	})
}

func TestStackSPUSHAfterSPOP(t *testing.T) {
	var stack Stack

	// Заполняем стек
	for i := 0; i < SIZE; i++ {
		stack.SPUSH(fmt.Sprintf("value%d", i+1))
	}

	// Извлекаем все значения
	for i := SIZE - 1; i >= 0; i-- {
		stack.SPOP()
	}

	t.Run("PushAfterSPOP", func(t *testing.T) {
		err := stack.SPUSH("newValue")
		if err != nil {
			t.Errorf("Expected SPUSH to succeed, but got error: %v", err)
		}
	})
}
