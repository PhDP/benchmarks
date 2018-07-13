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

fn conjunction(lhs: Formula, rhs: Formula) -> Formula {
  return Formula::Negation {
    child: Rc::new(
      Formula::Disjunction {
        lhs_child: Rc::new(Formula::Negation { child: Rc::new(lhs) }),
        rhs_child: Rc::new(Formula::Negation { child: Rc::new(rhs) })
      }
    )
  }
}

fn eval(f: &Formula, values: &HashSet<String>) -> bool {
  match f {
    Formula::Bottom => false,
    Formula::Variable { ref name } => values.contains(name),
    Formula::Negation { ref child } => !eval(child, values),
    Formula::Disjunction { ref lhs_child, ref rhs_child } => eval(lhs_child, values) || eval(rhs_child, values)
  }
}

#[cfg(test)]
mod tests {
  use super::*;
  use test::Bencher;

  #[bench]
  fn bench_formula0(b: &mut Bencher) {
    let mut values = HashSet::new();
    values.insert("b".to_string());
    values.insert("c".to_string());
    let f = conjunction(Formula::Disjunction { lhs_child: Rc::new(Formula::Bottom), rhs_child: Rc::new(Formula::Disjunction { lhs_child: Rc::new(Formula::Variable { name: "a".to_string() }), rhs_child: Rc::new(Formula::Negation { child: Rc::new(Formula::Variable { name: "b".to_string() }) }) }) }, top());
    b.iter(|| eval(&f, &values));
  }
}

