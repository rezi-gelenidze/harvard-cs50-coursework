

function copy(){
    var text = 'rezi.gelenidze.05@gmail.com';
    // Create textarea, assign text as its value and place it far in the viewport
    // then copy it into a clipboard and then remove text area
    var el = document.createElement('textarea');
    el.value = text;
    // Set non-editable to avoid focus and move outside of view
    el.setAttribute('readonly', '');

    el.style = {position: 'absolute', left: '-9999px'};
    document.body.appendChild(el);
    el.select();
    document.execCommand('copy');
    document.body.removeChild(el);
}