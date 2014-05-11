% Omid55
function [ result ] = GiveTheMatrix( filepath , isdigits )

data = importdata(filepath,'\n');

if isdigits == 1
    result = cell(length(data),1);
    for i = 1 : length(data)
        result{i} = str2num(data{i}); 
    end
else
    result = data;
end

disp([filepath ' is Done.']);

end

