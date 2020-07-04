clear
clc
path = 'decentralised\';
d=dir(strcat(path,'*.fig')); % capture everything in the directory with FIG extension
allNames={d.name}; % extract names of all FIG-files
close all; % close any open figures
for i=1:1%length(allNames)
	open(strcat(path,allNames{i})); % open the FIG-file
	base=strtok(allNames{i},'.'); % chop off the extension (".fig")
    legend = findobj(gcf,'Type','legend');
    set(legend,'FontName', 'Helvetica');
	print('-djpeg',base); % export to JPEG as usual
	close(gcf); % close it ("gcf" returns the handle to the current figure)
end
