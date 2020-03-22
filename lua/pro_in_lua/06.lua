names = {"Peter", "Paul", "Mary"}
grades = {Mary = 10, Paul = 7, Peter = 8}
table.sort(names, function (n1, n2) return grades[n1] > grades[n2] end)

function sortbygrade (names, grades)
    table.sort(names, function (n1, n2) return grades[n1] > grades[n2] end)
end

function newCounter()
    local i = 0
    return function()
       -- anonymous function
       i = i + 1
       return i
    end
end

c1 = newCounter()
print("c1() = "..c1()) --> 1
print("c1() = "..c1()) --> 1
c2 = newCounter()
print("c2() = "..c2()) --> 1
print("c1() = "..c1()) --> 3
print("c2() = "..c2()) --> 2
