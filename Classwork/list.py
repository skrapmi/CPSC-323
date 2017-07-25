

A = [1,2,3,2,1]

def last(A):
	return A[len(A)- 1]

def second(A):
	return A[1]

def nth(A, n):
	return A[n]

def numElems(A):
	return len(A)

def reverse(A):
	for i in range(len(A)/2):
		A[i], A[(len(A)-1) - i] = A[(len(A)-1) - i], A[i]
	return A		

def palindrome(A):
	for i in range(len(A)/2):
		if A[i] != A[(len(A)-1) - i]:
			return False
	return True
	
print "list A:", A[0:5]
print last(A)
print second(A)
print nth(A, 3)
print numElems(A)

print "list A:", reverse(A)[0:5]

print "A is a palindrome : ", palindrome(A)




