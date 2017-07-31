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
    Var (vId, dt) ->  Printf.printf "%s" vId
;;


let rec expEval = function
  |Value vVar -> varEval vVar 
  | Call (cf, cargs) -> 
      let funcEval = function
          Func (fid, fdta, fdtb) -> match fid with
          |"getint" -> Printf.printf "\na1 := &input\ncall %s\n" fid
          |"putint" -> Printf.printf "\na1 := &output\ncall %s\n" fid
          | _ -> Printf.printf "%s is not a valid function call...\n" fid

      in funcEval cf ;
        (*Printf.printf "with args ";
          let rec argsEval = function
          |[] -> ()
          |h::t -> expEval h ; argsEval t 
          in argsEval cargs *)
  | Neq (ne, ne2) -> Printf.printf "r1: = "; expEval ne ;
      Printf.printf "\nr2 := "; expEval ne2; 
      Printf.printf "\nr1 := r1 != r2\n if r1 goto L3\n";
  |Gt (ge, ge2) -> expEval ge; Printf.printf " > "; expEval ge2; 
  |Minus (me, me2) -> expEval me; Printf.printf "minus "; expEval me2; 
;;


let startP = function
    Program stmtList -> 
      let rec trav = function
        | [] -> ()
        | Assign(aVar, aExp)::t -> expEval aExp;
            (varEval aVar); Printf.printf" := r1 \n"  ; trav t
        | Expr eExp::t ->  expEval eExp; trav t
        | While (wExp, wList)::t -> Printf.printf "while "; expEval wExp;
            Printf.printf "\n  do: "; trav wList; trav t
        | If (ifExp, thenList, elseList)::t -> Printf.printf "L2: "; 
            expEval ifExp; trav t
      in trav stmtList;
        Printf.printf "a1 := &output\ncall writeln\ngoto exit\n"
;;



startP (Program
          [Assign (Var ("i", Int), Call (Func ("getint", Void, Int), []));
           Assign (Var ("j", Int), Call (Func ("getint", Void, Int), []));
           While (Neq (Value (Var ("i", Int)), Value (Var ("j", Int))),
                  [If (Gt (Value (Var ("i", Int)), Value (Var ("j", Int))),
                       [Assign (Var ("i", Int),
                                Minus (Value (Var ("i", Int)), 
                                       Value (Var ("j", Int))))],
                       [Assign (Var ("j", Int),
                                Minus (Value (Var ("j", Int)), 
                                       Value (Var ("i", Int))))])]);
           Expr (Call (Func ("putint", Int, Void), 
                       [Value (Var ("i", Int))]))] );;








