#ifndef __TOKEN_SEARCH_HPP__
#define __TOKEN_SEARCH_HPP__

#include "Connect_Four.hpp"
#include "Transposition_Table.hpp"

class Token_Search
{
private:

	enum class Evaluation_Tag
	{
		Exact,
		Lowerbound,
		Upperbound
	};

	struct Evaluated_Token
	{
		Token m_token{};

		int m_search_depth{};
		int m_ply_from_root{};

		int m_evaluation{};
		Evaluation_Tag m_evaluation_tag{};
	};

	inline Evaluated_Token make_exact_evaluated_token(Token const& token, const int search_depth, const int ply_from_root, const int evaluation) const;
	inline Evaluated_Token make_lower_bound_evaluated_token(Token const& token, const int search_depth, const int ply_from_root, const int evaluation) const;
	inline Evaluated_Token make_upper_bound_evaluated_token(Token const& token, const int search_depth, const int ply_from_root, const int evaluation) const;

	inline constexpr bool is_exact_evaluated_token(Evaluated_Token const& evaluated_token) const { return evaluated_token.m_evaluation_tag == Evaluation_Tag::Exact; }
	inline constexpr bool is_lower_bound_evaluated_token(Evaluated_Token const& evaluated_token) const { return evaluated_token.m_evaluation_tag == Evaluation_Tag::Lowerbound; }
	inline constexpr bool is_upper_bound_evaluated_token(Evaluated_Token const& evaluated_token) const { return evaluated_token.m_evaluation_tag == Evaluation_Tag::Upperbound; }
	

public:
	using transposition_table_type = Transposition_Table<Evaluated_Token>;

	Token_Search(Connect_Four const& connect_four, const int search_depth) : m_connect_four(connect_four), m_search_depth(search_depth) {}
	Token_Search() : Token_Search(Connect_Four{}, 0) {}

	Token find_optimum_move();

private:

	int negamax(int search_depth, int ply_from_root, int alpha, int beta);
	transposition_table_type::const_iterator load_transposition_table_record(const int search_depth, const int ply_from_root, const int alpha, const int beta);

private:

	int m_search_depth{};
	int m_base_win_evaluation{ 1000 };
	int m_base_neutral_evaluation{ 0 };

	int m_transpositions{ 0 };
	int m_nodes_searched{ 0 };
	int m_branches_pruned{ 0 };

	Evaluated_Token m_iterative_best_evaluated_token{};

	Connect_Four m_connect_four{};
	transposition_table_type m_transposition_table{ 64000 };
};

#endif