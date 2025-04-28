Env word is: Only alpha and underscore


# Parsing
is the same word if no operators
(quoted make ignore special chars, if touch quote so do part)
- split by pipes | not in quotes
- split by operator, <, >, <<, >> not in quotes -> next word = path/limiter
- expands if not quoted (can be just $)
- split by space, not in quotes
- remove quotes
- expand all
