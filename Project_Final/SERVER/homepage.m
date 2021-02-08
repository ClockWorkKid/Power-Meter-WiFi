function varargout = homepage(varargin)
% HOMEPAGE MATLAB code for homepage.fig
%      HOMEPAGE, by itself, creates a new HOMEPAGE or raises the existing
%      singleton*.
%
%      H = HOMEPAGE returns the handle to a new HOMEPAGE or the handle to
%      the existing singleton*.
%
%      HOMEPAGE('CALLBACK',hObjec t,eventData,handles,...) calls the local
%      function named CALLBACK in HOMEPAGE.M with the given input arguments.
%
%      HOMEPAGE('Property','Value',...) creates a new HOMEPAGE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before homepage_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to homepage_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help homepage

% Last Modified by GUIDE v2.5 06-Sep-2019 07:58:54

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @homepage_OpeningFcn, ...
    'gui_OutputFcn',  @homepage_OutputFcn, ...
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


% --- Executes just before homepage is made visible.
function homepage_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to homepage (see VARARGIN)

% Choose default command line output for homepage
handles.output = hObject;
handles.str2=[];
handles.str1=[];
handles.n=1;
handles.str=0;
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes homepage wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = homepage_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function username_Callback(hObject, eventdata, handles)
% hObject    handle to username (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of username as text
%        str2double(get(hObject,'String')) returns contents of username as a double


% --- Executes during object creation, after setting all properties.
function username_CreateFcn(hObject, eventdata, handles)
% hObject    handle to username (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function password_Callback(hObject, eventdata, handles)
% hObject    handle to password (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of password as text
%        str2double(get(hObject,'String')) returns contents of password as a double


% --- Executes during object creation, after setting all properties.
function password_CreateFcn(hObject, eventdata, handles)
% hObject    handle to password (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
function figure1_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles.n=1


% --- Executes on button press in login.
function figure1_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  structure with the following fields (see MATLAB.UI.FIGURE)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)
% password = get(hObject,'Userdata');
% key = get(figure1,'currentkey');
% switch key
%     case 'backspace'
%         password = password(1:end-1); % Delete the last character in the password
%     case 'return'  % This cannot be done through callback without making tab to the same thing
%         gui = getappdata(0,'logindlg');
%         OK([],[],gui.main);
%     case 'tab'  % Avoid tab triggering the OK button
%         gui = getappdata(0,'logindlg');
%         uicontrol(gui.OK);
%     case 'escape'
%         % Close the login dialog
%         Escape(fig,[])
%     otherwise
%         password = [password get(fig,'currentcharacter')]; % Add the typed character to the password
% end
% SizePass = size(password); % Find the number of asterisks
% if SizePass(2) > 0
%     asterisk(1,1:SizePass(2)) = '*'; % Create a string of asterisks the same size as the password
%     set(h,'String',asterisk) % Set the text in the password edit box to the asterisk string
% else
%     set(h,'String','')
% end
% set(h,'Userdata',password)
cc=get(handles.figure1,'CurrentCharacter');
% Get the current string in the edit and static text boxes
%What is in the edit box
str2=get(handles.username,'string');
str1=get(handles.password,'string');
if isempty(handles.str2)
    handles.str2=cc;
    guidata(hObject,handles);
    set(handles.username,'string',handles.str2);
else
    if ((~strcmp(eventdata.Key,'return')) && handles.n==1)
        handles.str2=strcat(handles.str2,cc);
        guidata(hObject,handles);
        set(handles.username,'string',handles.str2);
    else
        handles.n=0;
        guidata(hObject,handles);
        if strcmp(eventdata.Key,'return')
        else
            if(isempty(str1))
                str1='*';
                handles.str=cc;
                guidata(hObject,handles);
            else
                str1=strcat(str1,'*');
                handles.str=strcat(handles.str,cc);
                guidata(hObject,handles);
            end
            set(handles.password,'string',str1);
        end
    end
end

%load('d:\pp','str2');
% if (isempty(str1))
%     % Edit box has 'Enter Password'
%     % This letter is the start of the password
%     str1 = '*'
%     str = cc;
%     save('d:\pp','str');
% else
%     % Edit box has something besides 'Enter Password'
%     % This letter is the next letter in the password
%
%     str1 = strcat(str1,'*');
%     load('d:\pp','str');
%     str=strcat(str,cc);
% end
% % Update the strings
%
% set(handles.password,'string',str1);
function login_Callback(hObject, eventdata, handles)
% hObject    handle to login (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
load('d:\password','curps');
if strcmp(handles.str2,"sumaiya") && strcmp(handles.str,curps)
    close(homepage);
    figure(nextpage);
    %uicontrol('style','push','call','figure(''nextpage.fig'',''new Figure'') close(homepage)');
end


% --- Executes on key press with focus on figure1 and none of its controls.


% --- Executes on mouse press over figure background.
