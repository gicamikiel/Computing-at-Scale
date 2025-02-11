* #### How did you test your code? What are the limitations of your testing?

I tested both ScalarFunction classes and IntegrationRule classes using a unit test executable.

The PolynomialFunction class was tested using simple known results for polynames (example: roots of polynomial).

For the IntegrationRule classes, rules were tested on polynomials where an exact solution is expected.

Getting an exact result from the Chebyshev rule was not successfully done.

* #### What approach did you take to document your functions and driver program?

I used comments whenever appropriate. However, I mostly relied on the code itself being clear.

* #### How did you handle errors? Whow did you test your error handling strategy?

I throw exceptions whenever applicable to ensure that an invalid result does not go undetected. 

* #### Is your code robust to errors in the input files? How did you test this?

I take only command line input from a user. The error text is verbose and the user can try again after making a mistake.

* #### Are there any limitations in your implementation you are aware of? Do you have any ideas on how to address them?

No neat management of integration rule definitions. This is currently done in a dedicated header file with variable declarations, but this could be done with a class or a struct.

* ####  If you wanted to optimize the performance of your code, what approach would you take?

Look into if using "leaner" data structures will improve performance.

* ####  How would you extend your code to two or more dimensions?

The current classes are likely not equipped enough for a derived class to sufficiently implement 2D or more integrations. However, 1D only integration can be used when evaluating 2D or more integrations.

* #### Explain how you would handle a user defined function that takes additional parameters.

The user can create a derived class. There is currently no simpler less-programmatic way to do so in the program.

* #### Are there any ways you could handle arbitrary functions that are defined at runtime by the user for example in an input file?

A derived class can be defined that reads a specified input file in a new or overridden method.

