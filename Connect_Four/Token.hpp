#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

// A slightly different abstraction from the connect four move. Essentially a token represents the top-most
// token in a connect-four game. I.e, one can stack another on top of it OR reduce the stack.
// With this abstraction, the move generating logic is refactored from the main connect_four class as a `stack_vector' 

class Token
{
public:

	Token(const int index, const int stack_vector) : m_index(index), m_stack_vector(stack_vector) {}
	Token() : Token(0, 0) {}

	// These update the internal position of the token.
	void stack() { m_index += m_stack_vector; }
	void unstack() { m_index -= m_stack_vector; }

	// We require these functions for validating whether make/unmake are possible.
	// Though whether a move is possible or not is out of the remit of this class. 
	// We simply describe how the token will move, it is up to the game to verify 
	// the legality of said move in its own context.
	inline constexpr int get_index() const { return m_index; }
	inline constexpr int get_stack_index() const { return (m_index + m_stack_vector); }
	inline constexpr int get_unstack_index() const { return (m_index - m_stack_vector); }

	inline constexpr bool operator==(Token const& token) const { return (m_index == token.m_index); }

private:

	// Store both position of the token on a board and the direction in which stacking occurs.
	int m_index{};
	int m_stack_vector{};
};

#endif