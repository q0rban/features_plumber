// $Id$

/**
 * @file
 * Features Plumber js.
 */

Drupal.behaviors.featuresPlumberUi = function(context) {
  // By not filtering to context, this will call every time.
  Drupal.settings.featuresPlumberUiAction = Drupal.settings.featuresPlumberUiAction || $('#features-export-form').attr('action');
  var action = Drupal.settings.featuresPlumberUiAction;
  var form = $('#features-export-populated');

  //form.children().unwrap();
  $('.features-plumber-ui-plumbable', form).each(function () {
    var item = $(this);
    var component = item.attr('component');
    var componentVal = item.attr('component_val');
    $('input[component="' + component + '"][component_val="' + componentVal + '"]', form).prependTo(item);
  });

  // Form within a form. Eek!
  $('#features-export-form').submit(function () {
    form.remove();
    $(this).attr('action', action);
  });
}