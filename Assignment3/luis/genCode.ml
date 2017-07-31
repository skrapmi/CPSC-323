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
          |"getint" -> Printf.printf "a1 := &input\ncall readint\n" 
          |"putint" -> Printf.printf "a1 := &output\n";
              Printf.printf "r1 := ";
              let argsEval = function
                |[] -> Printf.printf "expected int argument...\n"
                |h::_ -> expEval h ;
              in argsEval cargs; 
                Printf.printf "\na2 = r1\n"; 
                Printf.printf "call writeint\n";
          | _ -> Printf.printf "%s is not a valid function call...\n" fid
      in funcEval cf ;
  | Neq (ne, ne2) -> Printf.printf "\nr1: = "; expEval ne ;
      Printf.printf "\nr2 := "; expEval ne2; 
      Printf.printf "\nr1 := r1 != r2\n";
  |Gt (ge, ge2) -> Printf.printf "r1 := "; expEval ge; 
      Printf.printf"\nr2 := "; expEval ge2; Printf.printf "\nr1 = r1 > r2\n";
      expEval ge2; Printf.printf " := r1\n"
  |Minus (me, me2) -> Printf.printf "r1 := "; expEval me; 
      Printf.printf"\nr2 := "; expEval me2; Printf.printf "\nr1 = r1 - r2\n";
;;


let startP = function
    Program stmtList -> Printf.printf "main:\n";
      let rec trav = function
        | [] -> ()
        | Assign(aVar, aExp)::t -> expEval aExp;
            (varEval aVar); Printf.printf" := r1 \n"  ; trav t
        | Expr eExp::t ->  expEval eExp; trav t
        | While (wExp, wList)::t -> Printf.printf "goto L1\n";
            Printf.printf "L2:\n";
            trav wList;  Printf.printf "L1: "; expEval wExp; 
            Printf.printf "if r1 goto L2\n";
            trav t
        | If (ifExp, thenList, elseList)::t ->  
            expEval ifExp; Printf.printf "if r1 goto L3\n";
            trav elseList; Printf.printf "goto L4\nL3: \n";
            trav thenList; Printf.printf "L4:\n";
            trav t
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








