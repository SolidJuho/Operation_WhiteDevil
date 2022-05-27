class FizzBuzz {
    
    private int cur;
    
    void FizzBuzz() {    
        cur = 0;
    }
    
    void run(int to) {
        
        for (int i = 1; i <= to; i++) {
            string ret = "";

            ret += buzzer(3, "Fizz");
            ret += buzzer(5, "Buzz");
            
            if (ret == "") {
                ret = i + "";
            }
            Print(ret);
        }
    }
    
    private string buzzer(int number, string append) {
        if (cur % number == 0) {
            return  append;
        }
        return "";
    }
}