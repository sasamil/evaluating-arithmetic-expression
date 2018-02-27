# evaluating-arithmetic-expression
New approach to the evaluating simple arithmetic expressions. Widely applicable, scalable and fast. Performance comparison with the classical approach.

This example demonstrate evaluations of simple arithmetic expressions. It has been inspired by my <a href="https://github.com/sasamil/parsing-arithmetic-expression">Haskell example</a>. It's not very likely that there can be anything new in the field of algorithms for parsing/evaluation of arithmetic expressions. However, I was googling a bit and so far, I have found nothing similar to this approach!? No stack, no state machine, no Shunting-Yard, no anything in this algorithm! So, I'll consider it new, for a while...

In this very example, the performances have been roughly compared. (a) Classical approach vs. (b) new-algorithm-1 vs. (c) new-algorithm-2. In other words: (Shunting-Yard -> rpn -> evaluation) vs. (new-algorithm -> rpn -> evaluation) -> vs. (new-algorithm -> in-place evaluation). It turns out that (b) is faster than (a), (c) is faster than (b). Moreover, (c) is about 40-50% faster than (a). By the way, the corectness of results and new algorithm in general, has been thoroughly unit-tested.

But, I would like to emphasize again - this approach is good because it is scallable. It should be very simple to add new operators and rules. I find it fairly simple, with a clear idea behind it.
