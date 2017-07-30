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


let rec getdt = function
  |Void -> "void"
  |Int -> "int"
;; 

let varEval = function
    Var (vId, dt) ->  
      Printf.printf "%s of type %s " vId (getdt dt)  
;;


let rec expEval = function
  |Value vVar -> Printf.printf "value " ; varEval vVar;
  | Call (cf, cargs) -> Printf.printf "call ";
      let funcEval = function
          Func (fid, fdta, fdtb) -> 
            Printf.printf "%s takes %s returns %s " fid (getdt fdta) (getdt fdtb)
      in funcEval cf ; 
        Printf.printf "with args ";
        let rec argsEval = function
          |[] -> ()
          |h::t -> expEval h ; argsEval t 
        in argsEval cargs
  | Neq (ne, ne2) -> expEval ne ; Printf.printf "!= "; expEval ne2  
  |Gt (ge, ge2) -> expEval ge; Printf.printf " > "; expEval ge2
  |Minus (me, me2) -> expEval me; Printf.printf "minus "; expEval me2
;;


let startP = function
    Program stmtList -> 
      let rec trav = function
        | [] -> ()
        | Assign(aVar, aExp)::t -> Printf.printf "assign " ; varEval aVar; 
            Printf.printf"to "; expEval aExp; print_newline(); trav t
        | Expr eExp::t -> Printf.printf "expression: " ; expEval eExp; 
            print_newline() ; trav t 
        | While (wExp, wList)::t -> Printf.printf "while "; expEval wExp;
            Printf.printf "\n  do: "; trav wList; trav t
        | If (iExp, iLista, iListb)::t -> Printf.printf "if "; expEval iExp;
            Printf.printf "\n  then: "; trav iLista; 
            Printf.printf "  else: "; trav iListb;  trav t
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









