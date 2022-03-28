//test expressions
int main() {
	lookahead = lexan(lexbuf);
	while (lookahead != DONE) expression();
	exit(EXIT_SUCCESS);
}

//test statement
int main() {
	lookahead = lexan(lexbuf);
	while (lookahead != DONE) statement();
	exit(EXIT_SUCCESS);
}

//test declaration
int main() {
	lookahead = lexan(lexbuf);
	while (lookahead != DONE) declaration();
	exit(EXIT_SUCCESS);
}

//final main
int main()
{
    lookahead = lexan(lexbuf);

    while (lookahead != DONE)
	globalOrFunction();

    exit(EXIT_SUCCESS);
}
