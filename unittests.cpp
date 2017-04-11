#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <tuple>

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

TEST_CASE("Tests or function", "[environment]")
{
	{
		std::string program = "(or False False)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(or False True)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(or True False False)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(or True True)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a False) (or a False))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a False) (or True a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::vector<std::string> programs = {"(or 4 5)", 
							"(or string string)",
							"(or True)",
					       	"(begin (define a soup) (or True a))",
					       	"(begin (define a 6) (or a True))"
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

TEST_CASE("Tests and function", "[environment]")
{
	{
		std::string program = "(and True False)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(and False False)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(and True False False)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(and True True)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a False) (and a False))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a True) (or True a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::vector<std::string> programs = {"(and 4 5)", 
							"(and string string)",
							"(and True)",
					       	"(begin (define a soup) (and True a))",
					       	"(begin (define a 6) (and a True))"
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

TEST_CASE("Tests not function", "[environment]")
{
	{
		std::string program = "(not False)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(not True)";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::string program = "(begin (define a False) (not a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(true));
	}

	{
		std::string program = "(begin (define a True) (not a))";
    	Expression result = runIt(program);
    	REQUIRE(result == Expression(false));
	}

	{
		std::vector<std::string> programs = {"(not 4)", 
							"(not string)",
							"(not True True)",
					       	"(begin (define a soup) (not a))",
					       	"(begin (define a 6) (not a))"
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

TEST_CASE("Tests define function", "[environment]")
{
	{
		std::string program = "(begin (define a (point 2 2)))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define a (point 2 2)) (define b a))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define a (point 2 2)) (define b a) (define c (line a b)))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define a (point 2 2)) (define b (point 2 2)) (define c (line a b)))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define a (point 2 2)) (define b (point 2 2)) (define c (line (point 2 2) b)))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define x True) (if x (define a (point 2 2)) (define b (point 2 2))))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define x False) (if x (define a (point 2 2)) (define b (point 2 2))))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value));
	}

	{
		std::string program = "(begin (define x True) (define r (point 2 2)) (define g (point 2 2)) (if x r g))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define x False) (define r (point 2 2)) (define g (point 2 2)) (if x r g))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value));
	}

	{
		std::string program = "(begin (define b True) (define a (point 2 2)))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define b potato) (define a (point 2 2)))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define b 6) (define a (point 2 2)))";
    	Expression result = runIt(program);
    	REQUIRE(std::get<0>(result.atom.point_value) == 2);
	}

	{
		std::string program = "(begin (define b 20) (define a b))";
    	Expression result = runIt(program);
    	REQUIRE(result.atom.double_value == 20);
	}

	{
		std::string program = "(begin (define b potato) (define a b))";
    	Expression result = runIt(program);
    	REQUIRE(result.atom.string_value == "potato");
	}

	{
		std::string program = "(begin (define b (line (point 1 1) (point 2 2))) (define a b) (+ 1 1))";
    	Expression result = runIt(program);
    	REQUIRE(result.atom.double_value == 2);
	}

	{
		std::string program = "(begin (define b (arc (point 1 1) (point 2 2) 5)) (define a b) (+ 1 1))";
    	Expression result = runIt(program);
    	REQUIRE(result.atom.double_value == 2);
	}

	{
		std::string program = "(begin (define mega 4) (define b (arc (point 1 1) (point mega 2) 5)) (define a b) (+ 1 1))";
    	Expression result = runIt(program);
    	REQUIRE(result.atom.double_value == 2);
	}

	{
		std::string program = "(begin (define mega (point 1 1)) (define megad (point 2 2)) (define b (arc mega megad 5)) (define a b) (+ 1 1))";
    	Expression result = runIt(program);
    	REQUIRE(result.atom.double_value == 2);
	}
}

TEST_CASE("Tests arctan function", "[environment]")
{
	{
		std::string program = "(begin (define one 1) (define zero 0) (arctan one zero) (+ 1 1))";
    	Expression result = runIt(program);
    	REQUIRE(result.atom.double_value == 2);
	}
}