x;
def f():
	x = x + 1
return x
def main():
	return def f()
 + def f()


# Boilerplat
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)
