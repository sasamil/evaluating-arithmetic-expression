# evaluating-arithmetic-expression
New approach to the arithmetic expressions evaluating. Performance comparison with the classical approach.

This example demonstrate evaluations of simple arithmetic expressions. It is inspired by the algorithm which has been explained in the <a href="https://github.com/sasamil/New-algorithm-for-parsing-arithmetic-expression">parsing-arithmetic-expression</a> repository. 

In this example however, the performances have been roughly compared.<br>(a) Classical approach&nbsp;&nbsp;&nbsp;vs.&nbsp;&nbsp;&nbsp;(b) new-algorithm-1&nbsp;&nbsp;&nbsp;vs.&nbsp;&nbsp;&nbsp;(c) new-algorithm-2

In other words:<br>(Shunting-Yard -> rpn -> evaluation)&nbsp;&nbsp;vs.&nbsp;&nbsp;(new-algorithm -> rpn -> evaluation)&nbsp;&nbsp;vs.&nbsp;&nbsp;(new-algorithm -> in-place evaluation)

It turns out that (b) is faster than (a), (c) is faster than (b). Moreover, (c) is about 60-70% faster than (a).

But, I would like to emphasize - in the first place, this approach is good because it is scallable. It should be very simple to add new operators and rules. I find it fairly simple, with a clear idea behind it. (please, note the simplicity of corresponding code)
