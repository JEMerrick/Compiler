def function(ba, ):
	if (a < b) :
		a = a - 1
		if (b < a) :
			b = b + 3
			if (a == b) :
				return a * b
		return b
	return 13
def main():
	return function(00, ) + function(21, ) + function(34, ) + function(76, )

# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
