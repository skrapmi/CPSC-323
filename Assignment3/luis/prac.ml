
let strSize  strList = 
  List.map(fun x -> String.length x) strList;;


let maxChars  = function
  |[] -> invalid_arg "empty list"
  | x :: xs -> List.fold_left max x xs;;

let formatStr n sChar sList = 
  String.concat (String.make n sChar) sList;;

let midStr n  hStr =
  String.concat hStr [formatStr ((n - String.length hStr)/2) ' ' ["|" ;""] ; 
                      formatStr ((n - String.length hStr)/2) ' ' ["" ;"|"] ];;

let mksign xList = 
  let strWidth = (maxChars (strSize xList) + 2) in 
  let bordStr = formatStr (strWidth) '-' ["+"; "+"] in 
  let rec mkHelper rList paramList =
    match paramList with
      |[] -> (rList @ [bordStr])
      |h::t-> if (List.hd xList) = h 
          then mkHelper ([bordStr] @ [midStr strWidth h]) t
          else mkHelper (rList @ [midStr strWidth h]) t
  in mkHelper [] xList ;;

let rec printStrList = function
  |[] -> print_endline "This is the end of the list"
  |h::t -> 
      begin 
        print_endline h;
        printStrList t;
      end ;;

printStrList (mksign ["hello"; "world"; "guy"; "!"]);;

