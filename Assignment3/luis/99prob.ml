let rec last = function
  | [] -> None
  | [x] -> Some x
  |_ :: t -> last t ;; 

let myList = [ 1; 3; 4; 6; 8];;

let rec lastTwo = function
  |[] | [_] -> None
  |[x; y] -> Some (x,y)
  |_::t -> lastTwo t;;

lastTwo myList

let rec at k t =
  match t with
    | [] -> None
    | h :: t -> match k with
      |1 -> Some h 
      | _ -> at (k-1) t;;


at 10 myList

let length xList = 
  let rec lengthHelper n t =
    match t with
      | [] -> n
      |_::t -> lengthHelper (n+1) t
  in lengthHelper 0 xList;;

length myList

let reverse pList = 
  let rec revHelper x y =
    match y with
      | [] -> x 
      | h::t -> revHelper (h::x) t 
  in revHelper [] pList;;
reverse myList
