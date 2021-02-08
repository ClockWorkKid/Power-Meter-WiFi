function varargout = history(varargin)
% HISTORY MATLAB code for history.fig
%      HISTORY, by itself, creates a new HISTORY or raises the existing
%      singleton*.
%
%      H = HISTORY returns the handle to a new HISTORY or the handle to
%      the existing singleton*.
%
%      HISTORY('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in HISTORY.M with the given input arguments.
%
%      HISTORY('Property','Value',...) creates a new HISTORY or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before history_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to history_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help history

% Last Modified by GUIDE v2.5 05-Sep-2019 15:08:16

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @history_OpeningFcn, ...
    'gui_OutputFcn',  @history_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before history is made visible.
function history_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to history (see VARARGIN)

% Choose default command line output for history
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes history wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = history_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in pop.
function pop_Callback(hObject, eventdata, handles)
load('d:\history_info','consume');
axes(handles.axes1);
choice=get(handles.pop,'value');
current_time = uint32(clock());
if choice==1
    show=zeros(1,24);
    show(1,1:current_time(4))=(1/3600)*consume(current_time(3),1:current_time(4),current_time(2));
    bar(show,0.5,'r');
    axis([0.5 24.5 0 max(show)]);
    xlabel('Hours of this day');
    ylabel('Consumed Power (Wh)');
end
if choice==2
    show=zeros(1,30);
    current_time=uint32(clock());
    for i=1:current_time(3)
        show(1,i)=(1/3600)*sum(consume(i,:,current_time(2)));
    end
    bar(show,0.5,'blue');
    axis([0.5 30.5 0 max(show)]);
    xlabel('Days of this month');
    ylabel('Consumed Power (Wh)');
end
if choice==3
    show=zeros(12,30);
    show1=zeros(1,12);
    for j=1:current_time(2)
        for i=1:30
            show(j,i)=sum(consume(i,:,j));
        end
        show1(1,j)=(1/3600)*sum(show(j,:));
    end
    bar(show1,0.5,'red');
    axis([0.5 12.5 0 max(show1)]);
    xlabel('Months of this year');
    ylabel('Consumed Power (Wh)');
end
    % hObject    handle to pop (see GCBO)
    % eventdata  reserved - to be defined in a future version of MATLAB
    % handles    structure with handles and user data (see GUIDATA)
    
    % Hints: contents = cellstr(get(hObject,'String')) returns pop contents as cell array
    %        contents{get(hObject,'Value')} returns selected item from pop
    
    
    % --- Executes during object creation, after setting all properties.
    function pop_CreateFcn(hObject, eventdata, handles)
    % hObject    handle to pop (see GCBO)
    % eventdata  reserved - to be defined in a future version of MATLAB
    % handles    empty - handles not created until after all CreateFcns called
    
    % Hint: popupmenu controls usually have a white background on Windows.
    %       See ISPC and COMPUTER.
    if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
        set(hObject,'BackgroundColor','white');
    end


% --- Executes on button press in back.
function back_Callback(hObject, eventdata, handles)
% hObject    handle to back (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close(history);
figure(nextpage);
