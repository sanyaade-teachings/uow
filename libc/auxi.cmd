@for %%x in (oldnames,uuid) do @(
	cl -nologo -Zl -c etc/%%x.c && lib -nologo %%x.obj
) 
