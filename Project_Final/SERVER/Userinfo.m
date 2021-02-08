function varargout = Userinfo(varargin)
% USERINFO MATLAB code for Userinfo.fig
%      USERINFO, by itself, creates a new USERINFO or raises the existing
%      singleton*.
%
%      H = USERINFO returns the handle to a new USERINFO or the handle to
%      the existing singleton*.
%
%      USERINFO('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in USERINFO.M with the given input arguments.
%
%      USERINFO('Property','Value',...) creates a new USERINFO or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Userinfo_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Userinfo_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Userinfo

% Last Modified by GUIDE v2.5 30-Aug-2019 22:57:59

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Userinfo_OpeningFcn, ...
                   'gui_OutputFcn',  @Userinfo_OutputFcn, ...
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


% --- Executes just before Userinfo is made visible.
function Userinfo_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Userinfo (see VARARGIN)

% Choose default command line output for Userinfo
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Userinfo wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Userinfo_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in updateinfo.
function updateinfo_Callback(hObject, eventdata, handles)
% hObject    handle to updateinfo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in changepassword.
function changepassword_Callback(hObject, eventdata, handles)
% hObject    handle to changepassword (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
a=findobj('Tag','changepassword');
if (isempty(a))
else
    close(Userinfo);
    figure(changeps);
end


% --- Executes on button press in back.
function back_Callback(hObject, eventdata, handles)
% hObject    handle to back (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close(Userinfo);
figure(nextpage);
