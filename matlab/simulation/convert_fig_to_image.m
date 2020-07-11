clear
clc
close all

path = 'decentralised\';
directory=dir(strcat(path,'decen_uncer*.fig')); % capture everything in the directory with FIG extension
names={directory.name}; % extract names of all FIG-files

for i=1:length(names)
	file = open(strcat(path,names{i})); % open the FIG-file
	base=strtok(names{i},'.'); % chop off the extension (".fig")
    handles = findobj(gcf,'Type','axes');
    for j=1:length(handles)
        legend(handles(j), 'off')
        legend(handles(j), 'show')
    end
    set(findall(gcf,'-property','FontSize'),'FontSize',22)
	print('-djpeg',base); % export to JPEG as usual
	close(gcf); % close it ("gcf" returns the handle to the current figure)
end
