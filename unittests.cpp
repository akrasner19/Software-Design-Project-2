#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "interpreter_semantic_error.hpp"
#include "interpreter.hpp"
#include "expression.hpp"
#include "test_config.hpp"

Expression runIt(const std::string & program){
  
  std::istringstream iss(program);
    
  Interpreter interp;
    
  bool ok = interp.parse(iss);
  if(!ok){
    std::cerr << "Failed to parse: " << program << std::endl; 
  }
  REQUIRE(ok);

  Expression result;
  REQUIRE_NOTHROW(result = interp.eval());

  return result;
}

TEST_CASE("Tests add function", "[environment]")
{
	{
		std::string program = "(+ 1 2)";
		std::istringstream iss(program);
 
  		Interpreter interp;

		bool ok = interp.parse(iss);

		REQUIRE(ok);
	}

	{
		std::string program = "(+ 1 2)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(3.));	
	}

	{
		std::string program = "(begin (define a 1) (+ a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(3.));	
	}

	{
		std::vector<std::string> programs = {"(+ 1)", 
					       	"(+ 1 a)",
					       	"(begin (define a True) (+ 1 a))",
					       	"(begin (define a st) (+ 1 a))",
					   		"(begin (define a st) (+ 1 b))"};
	    for(auto s : programs)
	    {
	    	Interpreter interp;

	    	std::istringstream iss(s);
	      
	    	bool ok = interp.parse(iss);
	    	REQUIRE(ok);

	    	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
	    }
	}
}

TEST_CASE("Tests sub function", "[environment]")
{
	{
		std::string program = "(- 2 1)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(1.));
	}

	{
		std::string program = "(begin (- 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(-2.));
	}

	{
		std::string program = "(begin (define a 1) (- a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(-1.));
	}

	{
		std::string program = "(begin (define a 1) (- a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(-1.));
	}

	{
		std::vector<std::string> programs = {"(- 1 1 1)", 
					       	"(- 1 a)",
					       	"(begin (define a True) (- 1 a))",
					       	"(begin (define a st) (- 1 a))",
					   		"(begin (define a st) (- 1 b))",
					   		"(begin (define a True) (- a 1))",
					       	"(begin (define a st) (- a 1))",
					   		"(begin (define a st) (- b 1))",//test doubles done
					   		"(begin (define a st) (- a))",
					   		"(begin (define a True) (- a))",
					   		"(begin (define a st) (- b))"};//test singles done
	    for(auto s : programs)
	    {
	    	Interpreter interp;

	    	std::istringstream iss(s);
	      
	    	bool ok = interp.parse(iss);
	    	REQUIRE(ok);

	    	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
	    }
	}
}

TEST_CASE("Tests div function", "[environment]")
{
	{
		std::string program = "(/ 4 2)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(2.));
	}

	{
		std::string program = "(begin (define a 4) (/ a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(2.));
	}

	{
		std::string program = "(begin (define a 2) (/ 4 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(2.));
	}

	{
		std::vector<std::string> programs = {"(/ 4 2 1)", 
					       	"(/ 4)",
					       	"(begin (define a True) (/ 4 a))",
					       	"(begin (define a st) (/ 4 a))",
					   		"(begin (define a st) (/ 4 b))",
					   		"(begin (define a True) (/ a 4))",
					       	"(begin (define a st) (/ a 4))",
					   		"(begin (define a st) (/ b 4))"
					   		};
	    for(auto s : programs)
	    {
	    	Interpreter interp;

	    	std::istringstream iss(s);
	      
	    	bool ok = interp.parse(iss);
	    	REQUIRE(ok);

	    	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
	    }
	}
}

TEST_CASE("Tests mult function", "[environment]")
{
	{
		std::string program = "(* 4 2)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(8.));
	}

	{
		std::string program = "(* 4 2 1)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(8.));
	}

	{
		std::string program = "(begin (define a 4) (* a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(8.));
	}

	{
		std::string program = "(begin (define a 2) (* 4 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(8.));
	}

	{
		std::vector<std::string> programs = {"(* 4)", 
					       	"(begin (define a True) (* 4 a))",
					       	"(begin (define a st) (* 4 a))",
					   		"(begin (define a st) (* 4 b))",
					   		"(begin (define a True) (* a 4))",
					       	"(begin (define a st) (* a 4))",
					   		"(begin (define a st) (* b 4))"
					   		};
	    for(auto s : programs)
	    {
	    	Interpreter interp;

	    	std::istringstream iss(s);
	      
	    	bool ok = interp.parse(iss);
	    	REQUIRE(ok);

	    	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
	    }
	}
}

TEST_CASE("Tests eq function", "[environment]")
{
	{
		std::string program = "(= 4 2)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(= 2 2)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 4) (= a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 2) (= 4 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 2) (= a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 2) (= 2 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::vector<std::string> programs = {"(= 4)", 
					       	"(begin (define a True) (= 4 a))",
					       	"(begin (define a st) (= 4 a))",
					   		"(begin (define a st) (= 4 b))",
					   		"(begin (define a True) (= a 4))",
					       	"(begin (define a st) (= a 4))",
					   		"(begin (define a st) (= b 4))"
					   		};
	    for(auto s : programs)
	    {
	    	Interpreter interp;

	    	std::istringstream iss(s);
	      
	    	bool ok = interp.parse(iss);
	    	REQUIRE(ok);

	    	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
	    }
	}
}

TEST_CASE("Tests geq function", "[environment]")
{
	{
		std::string program = "(>= 4 2)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(>= 2 4)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 4) (>= a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 2) (>= 4 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 2) (>= a 4))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 4) (>= 2 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::vector<std::string> programs = {"(>= 4)", 
					       	"(begin (define a True) (>= 4 a))",
					       	"(begin (define a st) (>= 4 a))",
					   		"(begin (define a st) (>= 4 b))",
					   		"(begin (define a True) (>= a 4))",
					       	"(begin (define a st) (>= a 4))",
					   		"(begin (define a st) (>= b 4))"
					   		};
	    for(auto s : programs)
	    {
	    	Interpreter interp;

	    	std::istringstream iss(s);
	      
	    	bool ok = interp.parse(iss);
	    	REQUIRE(ok);

	    	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
	    }
	}
}

TEST_CASE("Tests gt function", "[environment]")
{
	{
		std::string program = "(> 4 2)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(> 2 4)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 4) (> a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 2) (> 4 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 2) (> a 4))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 4) (> 2 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::vector<std::string> programs = {"(> 4)", 
					       	"(begin (define a True) (> 4 a))",
					       	"(begin (define a st) (> 4 a))",
					   		"(begin (define a st) (> 4 b))",
					   		"(begin (define a True) (> a 4))",
					       	"(begin (define a st) (> a 4))",
					   		"(begin (define a st) (> b 4))"
					   		};
	    for(auto s : programs)
	    {
	    	Interpreter interp;

	    	std::istringstream iss(s);
	      
	    	bool ok = interp.parse(iss);
	    	REQUIRE(ok);

	    	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
	    }
	}
}

TEST_CASE("Tests leq function", "[environment]")
{
	{
		std::string program = "(<= 4 2)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(<= 2 4)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 4) (<= a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 2) (<= 4 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 2) (<= a 4))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 4) (<= 2 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::vector<std::string> programs = {"(<= 4)", 
					       	"(begin (define a True) (<= 4 a))",
					       	"(begin (define a st) (<= 4 a))",
					   		"(begin (define a st) (<= 4 b))",
					   		"(begin (define a True) (<= a 4))",
					       	"(begin (define a st) (<= a 4))",
					   		"(begin (define a st) (<= b 4))"
					   		};
	    for(auto s : programs)
	    {
	    	Interpreter interp;

	    	std::istringstream iss(s);
	      
	    	bool ok = interp.parse(iss);
	    	REQUIRE(ok);

	    	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
	    }
	}
}

TEST_CASE("Tests lt function", "[environment]")
{
	{
		std::string program = "(< 4 2)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(< 2 4)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 4) (< a 2))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 2) (< 4 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a 2) (< a 4))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a 4) (< 2 a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::vector<std::string> programs = {"(< 4)", 
					       	"(begin (define a True) (< 4 a))",
					       	"(begin (define a st) (< 4 a))",
					   		"(begin (define a st) (< 4 b))",
					   		"(begin (define a True) (< a 4))",
					       	"(begin (define a st) (< a 4))",
					   		"(begin (define a st) (< b 4))"
					   		};
	    for(auto s : programs)
	    {
	    	Interpreter interp;

	    	std::istringstream iss(s);
	      
	    	bool ok = interp.parse(iss);
	    	REQUIRE(ok);

	    	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
	    }
	}
}