fun filter f nil = nil
  | filter f (h :: t) = if f h then h :: filter f t else filter f t;

fun quicksort nil = nil
  | quicksort (h :: t) =
	let
	    fun below x = x < h
	    fun above x = x >= h
	in
	    quicksort (filter below t) @ h :: quicksort (filter above t)
	end;


fun quicksort lst =
    if null lst then nil
    else
	let
	    fun below x = x < (hd lst)
	    fun above x = x >= (hd lst)
	in
	    quicksort (filter below (tl lst)) @ (hd lst) :: quicksort (filter above (tl lst))
	end;
