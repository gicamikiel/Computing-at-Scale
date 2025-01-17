#### How did you test your code? What are the limitations of your testing?

Results from the code were compared to matrix multiplication results from MATLAB. Only small matrices were used and large matrices were not tested.

#### What are the limitations of the matrix market format for dense matrices?

Not space efficient as space is being used to store zeros

#### If you know the size of the matrices at compile time, how would you change your code to take advantage of this information?

Use fixed size arrays, get rid of anything to do with allocating memory

#### Was your matrix representation row-major or column-major? How did you decide? Do you think this will have an impact on performance?

Row major as it has slightly simpler indexing logic in matrix-vector multiplication. It should not have an impact on performance.

#### What approach did you take to document your functions and driver program?

Help messages to stdout and comments

#### Is your code robust to errors in the input files? How did you test this?

No

#### Are there any limitations in your implementation you are aware of? Do you have any ideas on how to address them? e.g., what is the maximum size of the matrices you can handle?

Does not seem to work for large matrices due to segmentation fault errors

#### If you wanted to optimize the performance of your code, what approach would you take?

Learn more about memory allocation and do so efficiently


