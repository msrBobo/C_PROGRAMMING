require "readline"
require "csv"
require_relative "./my_sqlite_request_sqlite.rb"

time = Time.new
puts "MySQLite version 1 #{time.strftime("%Y/%d/%m")}"


class MySqliteCli
    
    def my_parser_sqlite_cli(str)
       s = str.split
       str = s

       str.each {|element|
       if element.include?(",")
        str[str.index(element)] = element.split(",")
       end
       if element.include?("=")
        str[str.index(element)] = element.split("=")
       end
    }
    str.flatten!
    0.upto(str.length-1)do |i|
    if str[i] != nil
        if str[i][0]=="("
            str[i].delete_prefix!("(")
            str.last.delete_suffix!(")")
        end
        if str[i][0]=="'" && str[i][str[i].length - 1] != "'"
            i += 1
            loop do
                    if str[i][str[i].length - 1] !="'"
                        str[i-1]<<""<<str[i]
                        str.delete_at(i)
                    else
                        str[i-1]<<""<< str[i]
                        str.delete_at(i)
                        break
                    end
                end
            end

        end
    end
    str
    end


    def run_sqlite_1!

        while buf = Readline.readline("my_cli>",true)
            r    = MySqliteRequest.new
            request = r
            wor   = ""
            key_word = wor
            word_1       = []
            select_columns = word_1
            ar_2      = []
            where_params_ar = ar_2
            ar_12 = []
            update_attributes_ar = ar_12
            er  = []
            values_ar = er
            my_parser_sqlite_cli(buf).each {|word|
            if word[0]=="'" && word[word.length-1]=="'"
                word.delete_prefix!("'").delete_suffix!("'")
            end

            case word.upcase
            when "SELECT"
                key_word = word
                request.instance_variable_set(:@type_of_request, :select)
                next
            when "INSERT"
                key_word = word
                request.instance_variable_set(:@type_of_request, :insert)
                next
            when "INTO"
                key_word = word
                next
            when "UPDATE"
                key_word = word
                request.instance_variable_set(:@type_of_request, :update)
                next
            when "DELETE"
                key_word = word
                request.instance_variable_set(:@type_of_request, :delete)
                next
            when "FROM"
                key_word = word
                next        
            when "WHERE"
                key_word = word
                next  
            when "SET"
                key_word = word
                next        
            when "VALUES"
                key_word = word
                next  
            end

            if key_word == ""
                invalid()
                exit
            end

            case key_word.upcase
            when "SELECT"
                select_columns<<word
                request.instance_variable_set(:@select_columns, select_columns)
                next
            when "INTO"
                request.instance_variable_set(:@table_name, word)
                next
            when "UPDATE"
                request.instance_variable_set(:@table_name, word)
                next
            when "FROM"
                request.instance_variable_set(:@table_name, word)
                headers = CSV.open(word,&:readline)
                next
            when "WHERE"
                where_params_ar<<word
                next
            when "SET"
                update_attributes_ar<<word
                next
            when "VALUES"
                values_ar<<word
                next
            end           
        }
        headers = CSV.open(request.instance_variable_get(:@table_name), &:readline)
        insert_attributes_hash = Hash[headers.zip(values_ar)].delete_if{|key,value| value ==nil}
        request.instance_variable_set(:@insert_attributes, insert_attributes_hash)
        request.instance_variable_set(:@where_params, where_params_ar.each_slice(2).to_a)

        request.instance_variable_set(:@update_attributes, update_attributes_ar.each_slice(2).to_h)

        request.run_csv   

        end
    end  

    def invalid()
        p "Input can't be blank! Use 'SELECT', 'INSERT', 'UPDATE', 'DELETE' for query"
    end


end

cli = MySqliteCli.new
msqcli = cli
msqcli.run_sqlite_1!