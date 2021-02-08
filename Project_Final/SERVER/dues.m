function varargout = dues(varargin)
% DUES MATLAB code for dues.fig
%      DUES, by itself, creates a new DUES or raises the existing
%      singleton*.
%
%      H = DUES returns the handle to a new DUES or the handle to
%      the existing singleton*.
%
%      DUES('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DUES.M with the given input arguments.
%
%      DUES('Property','Value',...) creates a new DUES or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before dues_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to dues_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help dues

% Last Modified by GUIDE v2.5 05-Sep-2019 14:34:35

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @dues_OpeningFcn, ...
                   'gui_OutputFcn',  @dues_OutputFcn, ...
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


% --- Executes just before dues is made visible.
function dues_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to dues (see VARARGIN)

% Choose default command line output for dues
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes dues wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = dues_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in back.
function back_Callback(hObject, eventdata, handles)
% hObject    handle to back (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close(dues);
figure(nextpage);


% --- Executes on selection change in listbox1.
function listbox1_Callback(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns listbox1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox1
current_time = uint32(clock());
load('d:\history_info','consume');
show=zeros(12,30);
show1=zeros(1,12);
    for j=1:current_time(2)
        for i=1:30
            show(j,i)=sum(consume(i,:,j));
        end
        show1(1,j)=sum(show(j,:));
    end
a=get(handles.listbox1,'Value');
for i=1:12
    if a==i
        b=strcat(num2str(show1(1,i)*2.5e-6),' Tk.');
        set(handles.bill,'string',b);
    end
end
% --- Executes during object creation, after setting all properties.
function listbox1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
