function varargout = nextpage(varargin)
% NEXTPAGE MATLAB code for nextpage.fig
%      NEXTPAGE, by itself, creates a new NEXTPAGE or raises the existing
%      singleton*.
%
%      H = NEXTPAGE returns the handle to a new NEXTPAGE or the handle to
%      the existing singleton*.
%
%      NEXTPAGE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in NEXTPAGE.M with the given input arguments.
%
%      NEXTPAGE('Property','Value',...) creates a new NEXTPAGE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before nextpage_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to nextpage_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help nextpage

% Last Modified by GUIDE v2.5 05-Sep-2019 14:19:05

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @nextpage_OpeningFcn, ...
                   'gui_OutputFcn',  @nextpage_OutputFcn, ...
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


% --- Executes just before nextpage is made visible.
function nextpage_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to nextpage (see VARARGIN)

% Choose default command line output for nextpage
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes nextpage wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = nextpage_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in livefeed.
function livefeed_Callback(hObject, eventdata, handles)
% hObject    handle to livefeed (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
a=findobj('Tag','livefeed');
if (isempty(a))
else
    close(nextpage);
    figure(livefeed);
end

% --- Executes on button press in history.
function history_Callback(hObject, eventdata, handles)
% hObject    handle to history (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)   
    close(nextpage);
    figure(history);

% --- Executes on button press in dues.
function dues_Callback(hObject, eventdata, handles)
% hObject    handle to dues (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close(nextpage);    
figure(dues);

% --- Executes on button press in userinfo.
function userinfo_Callback(hObject, eventdata, handles)
% hObject    handle to userinfo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close(nextpage);    
figure(Userinfo);
