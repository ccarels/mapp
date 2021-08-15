import sys

# Script uses variable n which was declared outside this scope.
# Provide a default if the script is used in a different context.
# This is also needed to satisfy coverage tests.
if not 'n' in globals():
    n = 10

print('Hello from Python!')
print(n)
print("Goodbye from Python!")
