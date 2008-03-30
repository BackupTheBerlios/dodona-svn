
c=0;

function onButton1Click()
	v=tonumber(getText("edit1"))
	n=v
	if v==nil then v=0; n="zero" end
	v=v*2
	setText("label1",n.." times two ="..v)
end

function onButton2Click()
	c=c+1
	setText("form1","button1 clicked "..c.." times")
end	

function VLG_EditButtonClick()
	if (isEditing("form1")==0) then
		setText("VLG_EditButton","Run Mode")
		setText("form1","** Edit mode **")
		editMode("form1",1)
	else
		setText("VLG_EditButton","Edit Mode")
		setText("form1","Form 1")
		editMode("form1",0)
	end
end	

