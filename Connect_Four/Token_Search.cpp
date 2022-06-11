#ifndef __TOKEN_SEARCH_CPP__
#define __TOKEN_SEARCH_CPP__

#include "Token_Search.hpp"

#include <iostream>

inline Token_Search::Evaluated_Token Token_Search::make_exact_evaluated_token(Token const& token, const int search_depth, const int ply_from_root, const int evaluation) const
{
	return Evaluated_Token{ token, search_depth, ply_from_root, evaluation, Evaluation_Tag::Exact };
}

inline Token_Search::Evaluated_Token Token_Search::make_lower_bound_evaluated_token(Token const& token, const int search_depth, const int ply_from_root, const int evaluation) const
{
	return Evaluated_Token{ token, search_depth, ply_from_root, evaluation, Evaluation_Tag::Lowerbound };
}

inline Token_Search::Evaluated_Token Token_Search::make_upper_bound_evaluated_token(Token const& token, const int search_depth, const int ply_from_root, const int evaluation) const
{
	return Evaluated_Token{ token, search_depth, ply_from_root, evaluation, Evaluation_Tag::Upperbound };
}

Token Token_Search::find_optimum_move()
{
	Evaluated_Token optimum{};
	
	int iterative_search_depth{ 1 };

	for (iterative_search_depth; iterative_search_depth <= m_search_depth; ++iterative_search_depth)
	{
		negamax(iterative_search_depth, 0, -std::numeric_limits<int>::max(), +std::numeric_limits<int>::max());
		optimum = m_iterative_best_evaluated_token;

		// If we have an evaluation, say 998 (i.e: can win in 2 forced moves MINIMUM), we don't need to search to any greater depth. 
		if ((optimum.m_evaluation) >= (m_base_win_evaluation - iterative_search_depth))
			break;
	}

	std::cout << "Found optimum token! [SEARCH_DEPTH=" << iterative_search_depth << "/" << (m_search_depth + 1)
		<< ", IDX=" << optimum.m_token.get_index()
		<< ", EVALUATION=" << optimum.m_evaluation
		<< ", EVALUATIONS=" << m_nodes_searched
		<< ", TRANSPOSITIONS=" << m_transpositions
		<< ", PRUNED_BRANCHES=" << m_branches_pruned << "]\n";

	return optimum.m_token;
}

int Token_Search::negamax(int search_depth, int ply_from_root, int alpha, int beta)
{
	// Attempt to look up position zobrist key in transposition table subject to it not being 'stale'.
	transposition_table_type::const_iterator transposition_table_iter = load_transposition_table_record(search_depth, ply_from_root, alpha, beta);

	// If we do not find end, then we have successfully looked up the key.
	if (transposition_table_iter != m_transposition_table.end())
	{
		// Update the number of successful transpositions
		++m_transpositions;

		if (ply_from_root == 0)
		{
			m_iterative_best_evaluated_token = transposition_table_iter->m_value;
		}

		// return the evaluation of the stored record.
		return transposition_table_iter->m_value.m_evaluation;
	}

	// TODO: refactor to a stand alone evaluator.
	if (search_depth == 0 || m_connect_four.is_state_terminal())
	{
		// The only real case worthy of evaluation is a win (at least in this current iteration).
		if (m_connect_four.get_state() == Connect_Four::State::Won)
		{
			// Note the negative sign to represent perspective.
			// I.e: every even ply will be positive and every odd negative.
			return -(m_base_win_evaluation - ply_from_root);
		}

		// Otherwise just return a netural evaluation (i.e 0) to reflect no significantly advantageous state.
		// This could be a drawn or inconclusive position.
		return m_base_neutral_evaluation;
	}

	// Hold the optimum token for this position.
	// TODO: Maybe just make this an evaluated_token...? 

	Token position_optimum_token{};
	Evaluation_Tag evaluation_tag{ Evaluation_Tag::Upperbound };

	for (Token& token : m_connect_four.stackable_tokens())
	{
		m_connect_four.stack_token(token);
		int position_optimum_evaluation = -negamax((search_depth - 1), (ply_from_root + 1), -beta, -alpha);
		m_connect_four.unstack_token(token);

		++m_nodes_searched;

		if (position_optimum_evaluation >= beta)
		{
			// Satisfaction of evaluation >= beta results in a lower-bound evaluation.
			evaluation_tag = Evaluation_Tag::Lowerbound;
			m_transposition_table.insert_record(m_connect_four.get_zobrist_key(), Evaluated_Token{ token, search_depth, ply_from_root, position_optimum_evaluation, evaluation_tag });

			// We will be able to prune this branch as the move is too advantageous for the opponent to allow it be played. 
			++m_branches_pruned;

			return beta;
		}

		// This represents the current best move.
		if (position_optimum_evaluation > alpha)
		{
			evaluation_tag = Evaluation_Tag::Exact;

			position_optimum_token = token;
			alpha = position_optimum_evaluation;

			if (ply_from_root == 0)
			{
				m_iterative_best_evaluated_token = Evaluated_Token{ token,search_depth, ply_from_root, position_optimum_evaluation, Evaluation_Tag::Exact };
			}
		}
	}

	m_transposition_table.insert_record(m_connect_four.get_zobrist_key(), Evaluated_Token{ position_optimum_token, search_depth, ply_from_root, alpha, evaluation_tag });
	return alpha;
}

Token_Search::transposition_table_type::const_iterator Token_Search::load_transposition_table_record(const int search_depth, const int ply_from_root, const int alpha, const int beta)
{
	// Attempt to look up position zobrist key in transposition table.
	transposition_table_type::const_iterator transposition_table_record = m_transposition_table.find(m_connect_four.get_zobrist_key());

	// If we cannot find an entry (i.e we return end) then return.
	if (transposition_table_record == m_transposition_table.end())
	{
		return transposition_table_record;
	}

	// Otherwise only return the evaluation if it satisfies it's description:
	// I.e for a lowerbound evaluation it is only useful if it is greater than the current beta.
	if (transposition_table_record->m_value.m_search_depth >= search_depth)
	{
		switch (transposition_table_record->m_value.m_evaluation_tag)
		{
		case Evaluation_Tag::Exact:
			return transposition_table_record;

		case Evaluation_Tag::Upperbound:
			return (transposition_table_record->m_value.m_evaluation <= alpha) ? transposition_table_record : m_transposition_table.end();

		case Evaluation_Tag::Lowerbound:
			return (transposition_table_record->m_value.m_evaluation >= beta) ? transposition_table_record : m_transposition_table.end();
		}
	}
	
	return m_transposition_table.end();
}


#endif