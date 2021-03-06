# Evaluating arithmetic expressions - reverse recursive algorithm
New approach to the arithmetic expressions evaluating. Performance comparison with the classical approach (Dijkstra's Shunting-Yard).

This example demonstrate performance gains when evaluationg arithmetic expressions by the algorithm which has been explained in the <a href="https://github.com/sasamil/parsing-arithmetic-expression">parsing-arithmetic-expression</a> repository.

So, these performance comparisons have been made here:<br>(a) Classical approach&nbsp;&nbsp;&nbsp;vs.&nbsp;&nbsp;&nbsp;(b) new-algorithm-1&nbsp;&nbsp;&nbsp;vs.&nbsp;&nbsp;&nbsp;(c) new-algorithm-2

In other words:<br>(Shunting-Yard -> RPN -> evaluation)&nbsp;&nbsp;vs.&nbsp;&nbsp;(new-algorithm -> RPN -> evaluation)&nbsp;&nbsp;vs.&nbsp;&nbsp;(new-algorithm -> in-place evaluation)

It turns out that (b) is faster than (a) and (c) is faster than (b). Moreover, <strong>(c) is for a magnitude faster than (a)</strong>.

Finally, I would like to emphasize - this new approach is good not only because it is faster. I find it scallable as well! It should be very simple to add new operators and rules. I find it fairly simple, with a clear idea behind it. (Note that the evaluation can be done <i>in-place</i>, without a need for intermediary data structures.)
