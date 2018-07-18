#![feature(test)]
extern crate test;

use std::rc::Rc;
use std::collections::HashSet;

/// A first-order logic formula.
enum Formula {
  Bottom,
  Variable { name: String },
  Negation { child: Rc<Formula> },
  Disjunction { lhs_child: Rc<Formula>, rhs_child: Rc<Formula> }
}

fn top() -> Formula {
  return Formula::Negation { child: Rc::new(Formula::Bottom) };
}

fn make_negation(f: Formula) -> Formula {
  return Formula::Negation { child: Rc::new(f) };
}

fn make_disjunction(lhs: Formula, rhs: Formula) -> Formula {
  return Formula::Disjunction { lhs_child: Rc::new(lhs), rhs_child: Rc::new(rhs) };
}

fn make_conjunction(lhs: Formula, rhs: Formula) -> Formula {
  return make_negation(make_disjunction(make_negation(lhs), make_negation(rhs)));
}

fn eval(f: &Formula, values: &HashSet<String>) -> bool {
  match f {
    Formula::Bottom => false,
    Formula::Variable { ref name } => values.contains(name),
    Formula::Negation { ref child } => !eval(child, values),
    Formula::Disjunction { ref lhs_child, ref rhs_child } => eval(lhs_child, values) || eval(rhs_child, values)
  }
}

fn eval_test() -> bool {
  let mut values = HashSet::new();
  values.insert("b".to_string());
  values.insert("c".to_string());
  let f = make_conjunction(make_disjunction(Formula::Bottom, make_disjunction(Formula::Variable { name: "a".to_string() }, make_negation(Formula::Variable { name: "b".to_string() }))), top());
  return eval(&f, &values);
}

#[cfg(test)]
mod tests {
  use super::*;
  use test::Bencher;
  use test::*;

  #[bench]
  fn bench_formula0(b: &mut Bencher) {
    b.iter(|| eval_test() );
  }
}
