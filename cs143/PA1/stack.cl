(*
 *  CS164 Fall 94
 *
 *  Programming Assignment 1
 *    Implementation of a simple stack machine.
 *
 *  Skeleton file
 *)

class Stack inherits A2I{
   item:Object;
   next:Stack;

   init(i:Object):Stack{
      {
         item <- i;
         self;
      }
   };

   push(i:Object):Stack{
      {
         let val:Object <-
            case i of
               i:Int => i2a(i);
               s:String => s;
               o:Object => {abort();};
            esac
            in
            if (isvoid i) then
               self
            else
               (new Stack).init(val).set_next(self)
            fi;
      }
   };

   set_next(i:Stack):Stack{
      {
         next <- i;
         self;
      }
   };

   pop():Stack{
      next
   };

   top():String{
      case item of
         i: Int => i2a(i);
         s: String => s;
         o: Object => "Unknown";
      esac
   };

};
(*aaaa*)
class StackCommand inherits A2I{
   command:String;
   stack:Stack;

   init(c:String,s:Stack):StackCommand{
      {
         command <- c;
         stack <- s;
         self;
      }
   };

   d(s:Stack):Stack{
      {
         let tmp:Stack <- s.pop() in
         while (not tmp.top() = "") loop
         {
               (new IO).out_string(tmp.top());
               (new IO).out_string("\n");
               tmp <- tmp.pop();
         }
         pool;
         s.pop();
      }

   };

   plus(s:Stack):Stack{
      {
         s.pop().pop().push(a2i(s.top())+a2i(s.pop().top()));
      }
   };


   swap(s:Stack):Stack{
      {
         let var_0:String <- s.top() in
         let var_1:String <- s.pop().top() in
         s.pop().pop().push(var_0).push(var_1);
      }
   };



};

class Main inherits IO {

   main() : Object {
      {
         let running:Bool <- true in {
            let input:Stack <- (new Stack) in {
               let command: StackCommand <- (new StackCommand) in {
                  command.init("",input);
                  input <- input.init("");
                  while (running) loop
                     {
                        out_string("> ");
                        let input_str: String <- in_string() in {
                           input <- input.push(input_str);
                           command.init(input_str,input);
                           if input.top() = "d" then
                              input <- command.d(input)
                           else 
                           {
                              if input.top() = "e" then
                              {
                                 input <- input.pop();
                                 if input.top() = "+" then
                                 {
                                    input <- input.pop();
                                    input <- command.plus(input);

                                 }
                                 else
                                    0
                                 fi;

                                 if input.top() = "s" then
                                 {
                                    input <- input.pop();
                                    input <- command.swap(input);
                                 }    
                                 else
                                    0
                                 fi;                
                              }
                              else
                                 0
                              fi;

                              if input.top() = "x" then
                              {
                                 input <- input.pop();
                                 running <- false;
                              }
                              else
                                 0
                              fi;
                           }
                           fi;
                        };                 
                     }
                  pool;
               };
            };
         };

      }
   };
};