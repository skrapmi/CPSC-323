(* Project: Assignment 3 
   Members: Luis Gonzalez, Timothy Parks, Stephen Cordasco

*)

type id = string
and data_type = Int | Void
and var = Var of id * data_type
and func = Func of id * data_type * data_type
and args = expr list
and expr =
    | Value of var
    | Call of func * args
    | Neq of expr * expr
    | Gt of expr * expr
    | Minus of expr * expr
and stmt =
    | Assign of var * expr 
    | Expr of expr
    | While of expr * stmt list
    | If of expr * stmt list * stmt list
and program = Program of stmt list ;;




let startP prgm = match prgm with 
    Program stmtList -> 
      let rec trav sList = match sList with
        |[] -> print_endline "done traversing!"
        | Assign(aVar, aExp)::t -> print_endline "assignment!" ;trav t
        | Expr eExp::t -> print_endline "expression!" ;
            let rec expEval e = match e with
              |Value v -> print_endline "value" 
              | Call (f, ags) -> print_endline "call"
              | Neq (ne, ne2) -> print_endline "neq" 
              |Gt (ge, ge2) -> print_endline "Gt"
              |Minus (me, me2) -> print_endline "Minus"
            in expEval eExp
             ; trav t 
        | While (wExp, wList)::t -> print_endline "while!"; trav t
        | If (iExp, iLista, iListb)::t -> print_endline "if!"; trav t
      in trav stmtList
;;



startP (Program
          [Assign (Var ("i", Int), Call (Func ("getint", Void, Int), []));
           Assign (Var ("j", Int), Call (Func ("getint", Void, Int), []));
           While (Neq (Value (Var ("i", Int)), Value (Var ("j", Int))),
                  [If (Gt (Value (Var ("i", Int)), Value (Var ("j", Int))),
                       [Assign (Var ("i", Int),
                                Minus (Value (Var ("i", Int)), Value (Var ("j", Int))))],
                       [Assign (Var ("j", Int),
                                Minus (Value (Var ("j", Int)), Value (Var ("i", Int))))])]);
           Expr (Call (Func ("putint", Int, Void), [Value (Var ("i", Int))]))] );;









