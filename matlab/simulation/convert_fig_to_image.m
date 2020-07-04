clear
clc
path = 'decentralised\';
d=dir(strcat(path,'*.fig')); % capture everything in the directory with FIG extension
allNames={d.name}; % extract names of all FIG-files
close all; % close any open figures
for i=1:length(allNames)
	file = open(strcat(path,allNames{i})); % open the FIG-file
	base=strtok(allNames{i},'.'); % chop off the extension (".fig")
    handles = findobj(gcf,'Type','axes');
    for j=1:length(handles)
        legend(handles(j), 'off')
        legend(handles(j), 'show')
    end
	print('-djpeg',base); % export to JPEG as usual
	close(gcf); % close it ("gcf" returns the handle to the current figure)
end
