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

class registers = object
  val mutable r = ["r1"; "r2"; "r3"; "r4"; "r5"]
  method nextreg = match r with
    | [] -> ""
    |h::t -> (r <- (t @ [h])); h
  method doneWregs = 
    r <- (List.sort compare r);
end;;

let reg = new registers;;


let rec getdt = function
  |Void -> "void"
  |Int -> "int"
;; 

let varEval = function
    Var (vId, dt) ->  print_string vId
;;


let expEval  e  = 
  let r1 = reg#nextreg in 
  let r2 = reg#nextreg in
  let rec exprec = function
    |Value vVar -> varEval vVar 
    | Call (cf, cargs) -> 
        let funcEval = function
            Func (fid, fdta, fdtb) -> match fid with
            |"getint" -> 
                Printf.printf "a1 := &input\ncall readint\n";
            |"putint" -> 
                Printf.printf "a1 := &output\n";
                Printf.printf "%s := " r1;
                let rec getArgs = function
                  |[] -> ()
                  | h::t -> exprec h; getArgs t; 
                in getArgs cargs;  print_newline();
                  Printf.printf "a2 = %s \ncall writeint\n" r1
            | _ -> () ;
        in funcEval cf ;                   
    | Neq (ne, ne2) ->
        Printf.printf "\n%s := " r1; exprec ne ;
        Printf.printf "\n%s := " r2; exprec ne2 ; 
        Printf.printf "\n%s := %s != %s\n" r1 r1 r2;
    |Gt (ge, ge2) -> Printf.printf "%s := " r1; exprec ge ; 
        Printf.printf"\n%s := " r2; exprec ge2 ; 
        Printf.printf "\n%s = %s > %s\n" r1 r1 r2;
    |Minus (me, me2) -> Printf.printf "%s := " r1; exprec me ; 
        Printf.printf"\n%s := " r2; exprec me2; 
        Printf.printf "\n%s = %s - %s\n" r1 r1 r2;
  in exprec e; reg#doneWregs;
;;


let codegen ast = 
  let r1 = reg#nextreg in
    match ast with
        Program stmtList -> Printf.printf "main: \n";
          let rec trav s label = match s with
            | [] -> ()
            | Assign(aVar, aExp)::t -> 
                expEval aExp ;
                (varEval aVar); Printf.printf" := %s \n" r1;
                trav t label
            | Expr eExp::t ->  expEval eExp  ; 
                trav t label
            | While (wExp, wList)::t -> 
                Printf.printf "goto L%d\n" label;
                Printf.printf "L%d:\n" (label + 1); 
                trav wList (label + 2);  
                Printf.printf "L%d: " label; expEval wExp ; 
                Printf.printf "if %s goto L%d\n" r1 (label + 1); 
                trav t label
            | If (ifExp, thenList, elseList)::t ->  
                expEval ifExp ; 
                Printf.printf "if %s goto L%d\n" r1 label; 
                trav elseList label; 
                Printf.printf "goto L%d\n" (label + 1); 
                Printf.printf "L%d:\n" (label);
                trav thenList label; 
                Printf.printf "L%d:\n" (label + 1); 
                trav t (label + 2)
          in trav stmtList 1; reg#doneWregs;
            Printf.printf "a1 := &output\ncall writeln\ngoto exit\n"
;;



codegen 
  (Program
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
      Expr (Call (Func ("putint", Int, Void), [Value (Var ("i", Int))]))]);;



(*
(Program
[If (Gt (Value (Var ("i", Int)), Value (Var ("j", Int))),
[Assign (Var ("i", Int),
Minus (Value (Var ("i", Int)), 
Value (Var ("j", Int))))],
[Assign (Var ("j", Int),
Minus (Value (Var ("j", Int)), 
Value (Var ("i", Int))))]);
If (Gt (Value (Var ("i", Int)), Value (Var ("j", Int))),
[Assign (Var ("i", Int),
Minus (Value (Var ("i", Int)), 
Value (Var ("j", Int))))],
[Assign (Var ("j", Int),
Minus (Value (Var ("j", Int)), 
Value (Var ("i", Int))))]);
While (Neq (Value (Var ("i", Int)), Value (Var ("j", Int))),
[If (Gt (Value (Var ("i", Int)), Value (Var ("j", Int))),
[Assign (Var ("i", Int),
Minus (Value (Var ("i", Int)), 
Value (Var ("j", Int))))],
[Assign (Var ("j", Int),
Minus (Value (Var ("j", Int)), 
Value (Var ("i", Int))))])])])
;;


*)






