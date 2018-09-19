# Evaluating arithmetic expressions - reverse recursive algorithm
New approach to the arithmetic expressions evaluating. Performance comparison with the classical approach (Dijkstra's Shunting-Yard).

This example demonstrate possible performance gains when evaluationg simple arithmetic expressions. It is inspired by the algorithm which has been explained in the <a href="https://github.com/sasamil/parsing-arithmetic-expression">parsing-arithmetic-expression</a> repository. Practically, that algorithm has just been implemented here for AE-evaluation.

In this example however, the performances have been roughly compared.<br>(a) Classical approach&nbsp;&nbsp;&nbsp;vs.&nbsp;&nbsp;&nbsp;(b) new-algorithm-1&nbsp;&nbsp;&nbsp;vs.&nbsp;&nbsp;&nbsp;(c) new-algorithm-2

In other words:<br>(Shunting-Yard -> RPN -> evaluation)&nbsp;&nbsp;vs.&nbsp;&nbsp;(new-algorithm -> RPN -> evaluation)&nbsp;&nbsp;vs.&nbsp;&nbsp;(new-algorithm -> in-place evaluation)

It turns out that (b) is faster than (a), (c) is faster than (b). Moreover, <i>(c) is for a magnitude faster than (a)</i>.

But, I would like to emphasize - in the first place, this approach is good because it is scallable. It should be very simple to add new operators and rules. I find it fairly simple, with a clear idea behind it. (Please note the simplicity of corresponding code. Note that the evaluation can be done <i>in-place</i>, without a need for intermediary data structures.)
