/*
 * Utility.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: mitthy
 */

#include "Semantic/Utility.h"
#include "Scope/Scope.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

void Cedomp::Semantic::CreateScope()
{
	Cedomp::Scope::Scope::getScope().generateScope();
	//Change to include function scope later
}

void Cedomp::Semantic::DestroyScope()
{
	Cedomp::Scope::Scope::getScope().deleteScope();
	//Change to include function scope later
}

Cedomp::Semantic::ContextHolder& Cedomp::Semantic::ContextHolder::get()
{
	static Cedomp::Semantic::ContextHolder ret;
	return ret;
}
Cedomp::Semantic::Context Cedomp::Semantic::ContextHolder::getContext()
{
	return this->context.back();
}

void Cedomp::Semantic::ContextHolder::setContext(
		Cedomp::Semantic::Context context )
{
	this->context.push_back(context);
}

void Cedomp::Semantic::ContextHolder::restoreContext()
{
	if (this->context.size() == 1)
	{
		std::cerr << "BUG: CONTEXT STACK EMPTY" << std::endl;
		std::exit(-1);
	}
	this->context.pop_back();
}

Cedomp::Semantic::ContextHolder::ContextHolder()
{
	context.push_back(Cedomp::Semantic::Context::GLOBAL);
}

void Cedomp::Semantic::ChangeContext( Cedomp::Semantic::Context context )
{
	Cedomp::Semantic::ContextHolder::get().setContext(context);
}

Cedomp::Semantic::Context Cedomp::Semantic::getContext()
{
	return Cedomp::Semantic::ContextHolder::get().getContext();
}

void Cedomp::Semantic::RestoreContext()
{
	Cedomp::Semantic::ContextHolder::get().restoreContext();
}

bool Cedomp::Semantic::ContextHolder::contains(
		Cedomp::Semantic::Context context )
{
	return std::find(this->context.begin(), this->context.end(), context)
			!= this->context.end();
}

bool Cedomp::Semantic::ContainsContext(
		Cedomp::Semantic::Context context )
{
	return Cedomp::Semantic::ContextHolder::get().contains(context);
}
