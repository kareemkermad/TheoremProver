# Theorem Prover

## Introduction
This is an implementation of a tableau theorem prover for propositional logic in the C programming language.
The program is able to parse propositional formulas and construct a tableau with the formula at the root which works by manipulating and
analysing its syntax in order to find out whether there is something that can falsify it. Given a formula, the tableau will tell us whether 
or not it is satisfiable.

## Features
* Parsing propositional logic formulas.
* Determining whether a propositional formula is satisfiable or not.
* Determining whether a propositional formula is valid or not.

## Grammar
prop ::= p | q | r | x | y | w <br />
fm ::= prop | -fm | (fm v fm) | (fm > fm) | (fm ^ fm)

\- is for logical negation (NOT) <br />
v is for logical disjunction (OR) <br />
\> is for logical implication (IMPLIES) <br />
\^ is for logical conjunction (AND)

## Semantics
Given a valuation λ : prop → {T, ꓕ} which extends to a truth-function satisfying:
<br /> <br />
![](https://latex.codecogs.com/png.latex?%5Cinline%20%5Cdpi%7B80%7D%20%5CLARGE%20%5C%5C%20%5Cindent%20%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%5C%2C%20%5Clambda%20%5Cleft%20%28%20%5Cneg%20%5Cphi%20%5Cright%20%29%20%3D%20%5Ctop%20%5Ciff%20%5Clambda%20%5Cleft%20%28%20%5Cphi%20%5Cright%20%29%20%3D%20%5Cbot%20%5C%5C%20%5Cindent%20%5C%2C%5C%2C%5C%2C%20%5Clambda%20%5Cleft%20%28%20%5Cphi%20%5Cwedge%20%5Cpsi%20%5Cright%20%29%20%3D%20%5Ctop%20%5Ciff%20%5Clambda%20%5Cleft%20%28%20%5Cphi%20%5Cright%20%29%20%3D%20%5Clambda%20%5Cleft%20%28%20%5Cpsi%20%5Cright%20%29%20%3D%20%5Ctop%20%5C%5C%20%5Cindent%20%5C%2C%5C%2C%5C%2C%20%5Clambda%20%5Cleft%20%28%20%5Cphi%20%5Cvee%20%5Cpsi%20%5Cright%20%29%20%3D%20%5Ctop%20%5Ciff%20%5Clambda%20%5Cleft%20%28%20%5Cphi%20%5Cright%20%29%20%3D%20%5Ctop%20%5C%2C%20or%20%5C%2C%20%5Clambda%20%5Cleft%20%28%20%5Cpsi%20%5Cright%20%29%20%3D%20%5Ctop%20%5C%5C%20%5Cindent%20%5Clambda%20%5Cleft%20%28%20%5Cphi%20%5Crightarrow%20%5Cpsi%20%5Cright%20%29%20%3D%20%5Ctop%20%5Ciff%20%5Clambda%20%5Cleft%20%28%20%5Cphi%20%5Cright%20%29%20%3D%20%5Cbot%20%5C%2C%20or%20%5C%2C%20%5Clambda%20%5Cleft%20%28%20%5Cpsi%20%5Cright%20%29%20%3D%20%5Ctop)
<br /> <br />
We say that:
* Φ is **valid** if λ(Φ) = T for all possible valuations λ
* Φ is **satisfiable** if λ(Φ) = T for at least one valuation λ
* Φ is **valid** if and only if ¬Φ is **unsatisfiable**

## Definitions
* A **literal** is a proposition or its negation (e.g. p, ¬p)
* A **theory** Σ is a set of propositional formulas
* If p,¬p ∈ Σ then the theory is **contradictory**, write C(Σ)
* If each formula in Σ is a literal then the theory is **fully expanded**, write Exp(Σ)
* A **tableau** is a list of theories.

## Tableau Algorithm
<img src="https://user-images.githubusercontent.com/37254625/119204512-7e79d200-ba8d-11eb-8bff-bae01f29578d.png" width="600" height="407">

The algorithm is **sound** (if Φ is satisfiable then its tableau will never close) and **complete** (if Φ is not satisfiable then its tableau will close) 
and is guaranteed to terminate in at most 2<sup>|Φ|</sup> steps.

## TODO
* Parser and tableau algorithm for first-order logic (not guaranteed to terminate but is sound and complete).
* Parser and tableau algorithm for modal logic.

