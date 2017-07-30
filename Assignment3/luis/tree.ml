type 'a tree = 
    | Empty
    | Node of 'a * 'a tree * 'a tree;;



let rec inorder t =
  match t with 
    | Empty -> []
    | Node (v, left, right) -> inorder left @ [v] @ inorder right;;


inorder (Node ('R', Node ('X', Empty, Empty), 
               Node ('Y', Node ('Z', Empty, Empty), Node('W', Empty, Empty))));;

